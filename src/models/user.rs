use serde::{Deserialize, Serialize};
use mongodb::bson::{DateTime, oid::ObjectId};
use validator::Validate;



#[derive(Debug, Serialize, Deserialize, Validate)]
pub struct User {
    #[serde(rename = "_id", skip_serializing_if = "Option::is_none")]
    pub id: Option<ObjectId>,
    #[validate(length(min = 3, message = "ID 길이가 최소 3 이상이어야 합니다."))]
    pub name: String,
    #[validate(length(min = 6, max = 256, message = "패스워드 길이는 6자 이상이어야합니다."))]
    pub password: String,
    #[validate(email(message = "Email must be a valid email address"))]
    pub email: String,
    // #[validate(range(min = 1, max = 120, message = "Age must be between 1 and 120"))]
    pub birth: DateTime,
}


#[derive(Debug, Serialize, Deserialize, Validate)]
pub struct Login
{
    pub name: String,
    pub password: String,
}