#include "register_types.h"


#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

// #include "test.h"
#include "tetris/block.h"
#include "tetris/engine.h";


using namespace godot;


void initialize_module(ModuleInitializationLevel _level)
{
    if (_level != MODULE_INITIALIZATION_LEVEL_SCENE)
        return;
    
    
    // GDREGISTER_CLASS(ChaosExample);
    GDREGISTER_CLASS(Tetris)
    GDREGISTER_CLASS(Block);
    GDREGISTER_CLASS(IBlock);
    GDREGISTER_CLASS(LBlock);
    GDREGISTER_CLASS(Square);
    GDREGISTER_CLASS(ZBlock);
    GDREGISTER_CLASS(ReverseZBlock);
}


void uninitialize_module(ModuleInitializationLevel _level)
{
    if (_level != MODULE_INITIALIZATION_LEVEL_SCENE)
        return;
}

extern "C"{
    GDExtensionBool GDE_EXPORT cpp_easylib(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
        godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

        init_obj.register_initializer(initialize_module);
        init_obj.register_terminator(uninitialize_module);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}