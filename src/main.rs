use std::sync::Mutex;

use actix_web::{App, HttpResponse, HttpServer, Responder, get, web::{self, scope}};
use mongodb::Collection;
use serde::Deserialize;
// use crate::models::user::User;
// use crate::db::connection::get_db;
// use crate::handlers::user_handlers::{
//     create_user,
//     // get_users,
//     update_user,
//     delete_user,

//     login_user
// };

use dyf::{dformat, FormatString};


use log::info;
use env_logger;

// mod errors;
// mod models;
// mod db;
// mod handlers;


const PORT: u16 = 3000;

struct TotalVisitorState
{
    visitor_count: Mutex<usize>,
}


async fn index(
    data: web::Data<TotalVisitorState>
) -> String
{
    let mut visit_count = data.visitor_count.lock().unwrap();
    *visit_count += 1;

    let introduce = FormatString::from_string("Hello from Blade and Blood Channel.\n
        당신은 {} 번째 방문자입니다.\n
        하지만 이곳에는 아직 아무것도 없습니다.".to_string()).unwrap();
    let fmt = dformat!(&introduce, *visit_count).unwrap();

    fmt
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

    // let db = get_db().await.expect("Failed to connect to MongoDB");
    
    // let collection: Collection<User> = db.collection("users");

    let visitor_counter = web::Data::new(TotalVisitorState {
            visitor_count: Mutex::new(0)
        });

    HttpServer::new(move || {
        App::new()
            .app_data(visitor_counter.clone()).route("/", web::get().to(index))
            // .route("/user", web::get().to(get_user))
            
            // 회원등록
    })
    .bind((post_ip, PORT))? // 포트번호를 깃허브로 뺄까 싶다.
    .run()
    .await
}

// docker run -d -p 3000:3000 --name blade-and-blood-container -e MONGO_USER='${{ secrets.MONGO_USER }}' -e MONGO_PASSWORD='${{ secrets.MONGO_PASSWORD }}' -e MONGO_HOST='${{ secrets.MONGO_HOST }}' -e MONGO_DB='${{ secrets.MONGO_DB }}' aaasssss231/blade-and-blood