use godot::prelude::*;


struct RustEasylib;


mod time_square;


#[gdextension()]
unsafe impl ExtensionLibrary for RustEasylib
{

}
