use actix_web::post;
use actix_web::{web, HttpResponse};

use argon2::Argon2;
use argon2::PasswordHash;
use argon2::PasswordHasher;
use argon2::PasswordVerifier;
use argon2::password_hash::SaltString;
use argon2::password_hash::rand_core::OsRng;

use mongodb::{bson::doc, Collection};
use serde::{Serialize, Deserialize};

use crate::models::user::User;
use crate::models::user::Login;

use futures::stream::TryStreamExt;
use log::{info, error};
use validator::Validate;



#[derive(Deserialize)]
struct UserRequest {
    username: String,
    password: String
}


#[derive(Serialize)]
struct UserAuth {
    id: i32,
    username: String,
    password_hash: String,
}


fn generate_password(password: String) -> String {
    let salt = SaltString::generate(&mut OsRng);
    let argon2 = Argon2::default();

    let hash_password = argon2.hash_password(&password.as_bytes(), &salt).unwrap().to_string();

    hash_password
}


fn verify_password(password: String, hash_password: String) -> Result<(), argon2::password_hash::Error> {
    let argon2 = Argon2::default();
    let parsed_password = PasswordHash::new(&hash_password).unwrap();
    argon2.verify_password(password.as_bytes(), &parsed_password)
}


// 유저 등록
#[post("/user/registry")]
pub async fn create_user(
    user: web::Json<User>,
    collection: web::Data<Collection<User>>,
) -> HttpResponse {
    if let Err(validation_errors) = user.validate() {
        error!("Validation failed: {:?}", validation_errors);
        return HttpResponse::BadRequest().json(validation_errors);
    }

    let mut user = user.into_inner();
    user.id = None; // Ensure the ID is not set by the client

    match collection.insert_one(user, None).await {
        Ok(insert_result) => {
            info!("User created: {:?}", insert_result.inserted_id);
            HttpResponse::Created().json(insert_result.inserted_id)
        }
        Err(e) => {
            error!("Failed to create user: {}", e);
            HttpResponse::InternalServerError().body("Failed to create user")
        }
    }
}



pub async fn login_user(
    id: web::Json<Login>,
) -> HttpResponse
{

    HttpResponse::InternalServerError().body("Failed to login")
}




// 유저 리스트
// pub async fn get_users(
//     collection: web::Data<Collection<User>>,
// ) -> HttpResponse {
//     match collection.find(None, None).await {
//         Ok(mut cursor) => {
//             let mut users = Vec::new();
//             // Collect all users into a vector
//             while let Ok(Some(user)) = cursor.try_next().await {
//                 users.push(user);
//             }
//             info!("Fetched {} users", users.len());
//             HttpResponse::Ok().json(users)
//         }
//         Err(e) => {
//             error!("Failed to fetch users: {}", e);
//             HttpResponse::InternalServerError().body("Failed to fetch users")
//         }
//     }
// }

// ID를 통해 유저 수정
pub async fn update_user(
    id: web::Path<String>,
    user: web::Json<User>,
    collection: web::Data<Collection<User>>,
) -> HttpResponse {
    // Validate input
    if let Err(validation_errors) = user.validate() {
        error!("Validation failed: {:?}", validation_errors);
        return HttpResponse::BadRequest().json(validation_errors);
    }

    let oid = match mongodb::bson::oid::ObjectId::parse_str(&*id) {
        Ok(oid) => oid,
        Err(_) => {
            error!("Invalid ID format: {}", id);
            return HttpResponse::BadRequest().body("Invalid ID format");
        }
    };

    let filter = doc! { "_id": oid };
    let update = doc! {
        "$set": {
            "name": user.name.clone(),
            "email": user.email.clone(),
            "birth": user.birth.clone()
        }
    };

    match collection.update_one(filter, update, None).await {
        Ok(result) if result.modified_count > 0 => {
            info!("User updated: {}", id);
            HttpResponse::Ok().body("User updated")
        }
        Ok(_) => {
            info!("User not found: {}", id);
            HttpResponse::NotFound().body("User not found")
        }
        Err(e) => {
            error!("Failed to update user: {}", e);
            HttpResponse::InternalServerError().body("Failed to update user")
        }
    }
}


// 유저 삭제
pub async fn delete_user(
    id: web::Path<String>,
    collection: web::Data<Collection<User>>,
) -> HttpResponse {
    // 오브젝트 ID로 변환
    let oid = match mongodb::bson::oid::ObjectId::parse_str(&*id) {
        Ok(oid) => oid,
        Err(_) => {
            error!("Invalid ID format: {}", id);
            return HttpResponse::BadRequest().body("Invalid ID format");
        }
    };

    let filter = doc! { "_id": oid };

    match collection.delete_one(filter, None).await {
        Ok(result) if result.deleted_count > 0 => {
            info!("User deleted: {}", id);
            HttpResponse::Ok().body("User deleted")
        }
        Ok(_) => {
            info!("User not found: {}", id);
            HttpResponse::NotFound().body("User not found")
        }
        Err(e) => {
            error!("Failed to delete user: {}", e);
            HttpResponse::InternalServerError().body("Failed to delete user")
        }
    }
}