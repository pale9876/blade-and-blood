use serde::{Deserialize, Serialize};
use mongodb::bson::oid::ObjectId;
use validator::Validate;


#[derive(Debug, Serialize, Deserialize, Validate)]
pub struct UserInfo
{
    pub id: ObjectId,
    pub lv: usize,
    pub gold: usize,
}