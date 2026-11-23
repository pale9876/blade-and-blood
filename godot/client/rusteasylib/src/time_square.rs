use godot::prelude::*;

#[derive(GodotClass)]
#[class(init, singleton, base=Node)]
struct TimeSquare
{
    scale: f32,
    

    base: Base<Node>
}