use std::sync::Mutex;

use actix_web::{
    App,
    HttpResponse,
    HttpServer,
    Responder,
    get,
    post,
    web::{self, scope}
};
use mongodb::{
    Client,
    Collection,
    Database,
    bson::{doc, oid::ObjectId}
};

use serde::{Deserialize, Serialize};
use crate::db::connection::get_db;
use dyf::{dformat, FormatString};
use serde_json::{self, json};

use log::info;
use env_logger;

mod db;


const PORT: u16 = 3000;
const DB_NAME: &str = "idle_game";


struct DBState
{
    visitor_count: Mutex<usize>,
}


#[get("/")]
async fn index(
    db: web::Data<Database>,
) -> impl Responder
{
    let _collection = db.collection::<DBState>("state");
    

    HttpResponse::Ok().body("")
}



#[derive(Debug, Serialize, Deserialize)]
struct UserInfo
{
    username: String,
    password_hashed: String,
    email: String,
    birth: String,

    #[serde(skip_serializing_if = "Option::is_none")]
    id: Option<ObjectId>,
}


#[derive(Debug, Deserialize)]
struct CreateUser {
    username: String,
    password_hashed: String,
    email: String,
    birth: String,
}

#[derive(Debug, Deserialize)]
struct GetUserQuery
{

}


#[derive(Debug, Serialize, Deserialize)]
struct ErrorMessage
{
    message: String,
}


#[derive(Serialize)]
struct Response {
    message: String,
}

struct AppState
{
    userinfo: UserInfo,
}


#[post("/registry")]
async fn registry(
    collection: web::Data<Collection<UserInfo>>,
    data: web::Json<CreateUser>
) -> impl Responder
{
    let user_data = data.into_inner();

    let user = UserInfo
    {
        id: None,
        username : user_data.username,
        email: user_data.email,
        birth: user_data.birth,
        password_hashed: user_data.password_hashed
    };

    if let Ok(result) = collection.insert_one(user, None).await
    {
        let id = result.inserted_id
            .as_object_id()
            .unwrap_or_else(ObjectId::new);

        return HttpResponse::Created().json(
            json!({
                "message": "Success",
                "id": &id.to_hex()
            })
        );
    }

    HttpResponse::InternalServerError().json(
        json!({
            "success": false,
            "message": "error"
        })
    )
}


#[actix_web::main]
async fn main() -> std::io::Result<()> {
    // 환경로그
    env_logger::Builder::new()
        .filter_level(log::LevelFilter::Info)
        .init();
    
    let current_os = std::env::consts::OS;
    let post_ip = if current_os == "windows" { "127.0.0.1" } else { "0.0.0.0" };
    
    info!("Starting server...");

    // init db
    let db = get_db().await.expect("Failed to connect to MongoDB");


    // collections
    let user_collection = web::Data::new(db.collection::<UserInfo>("user"));

    HttpServer::new(move || {
        App::new()
            .app_data(db.clone())
            .app_data(user_collection.clone())
            // 회원등록
            .service(registry)
            .service(index)
    })
    .bind((post_ip, PORT))? // 포트번호를 깃허브로 뺄까 싶다.
    .run()
    .await
}
