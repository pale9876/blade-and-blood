#include "tetris.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;


void Tetris::_bind_methods()
{
    // Signal
    ADD_SIGNAL(MethodInfo("ticked"));

    // Methods
    ClassDB::bind_method(D_METHOD("tick"), &Tetris::tick);
    ClassDB::bind_method(D_METHOD("cast"), &Tetris::cast);
    ClassDB::bind_method(D_METHOD("get_state"), &Tetris::get_state);
    ClassDB::bind_method(D_METHOD("reinit"), &Tetris::reinit);

    // SetGet
    ClassDB::bind_method(D_METHOD("resize", "_size"), &Tetris::resize, Vector2i(10, 20));
    ClassDB::bind_method(D_METHOD("get_size"), &Tetris::get_size);
    
    ClassDB::bind_method(D_METHOD("get_cursor"), &Tetris::get_cursor);
    ClassDB::bind_method(D_METHOD("get_prev"), &Tetris::get_prev);
    
    ClassDB::bind_method(D_METHOD("init_cursor", "_block"), &Tetris::init_cursor);
    ClassDB::bind_method(D_METHOD("init_prev", "_block"), &Tetris::init_prev);
    ClassDB::bind_method(D_METHOD("search_completed_line"), &Tetris::search_completed_line);
}



Coords Tetris::coordinated(Met &metris)
{
    for (int y = 0; y < metris.size(); y+=1)
    {
        for (int x = 0; x < metris.size(); x+=1)
        {
            
        }
    }
}


Met Tetris::Mapping(Vector2i coord, Coords _origin, Met state)
{


    return Met();
}



void Tetris::_enter_tree()
{
    if (Engine::get_singleton() -> is_editor_hint())
        return;
}


Tetris::Tetris()
{
    size = DEFAULT_SIZE;
    
    if (!Engine::get_singleton() -> is_editor_hint())
    {
        state = _init_state();
    }
}

Met Tetris::cursor_merge_to_state()
{
    if (this->cursor == nullptr)
    {
        UtilityFunctions::printerr("Error Confirmed");
        return {};
    }

    Met current_state = this->state.duplicate();
    Vector2i _point = this->cursor->coord;
    Met metris = this->cursor->metris;
    
    Vector2i target_size = Vector2i(
        Line(metris[0]).size(),
        metris.size()
    );
    
    for (int y = 0; y < target_size.y; y += 1)
    {
        for (int x = 0; x < target_size.x; x += 1)
        {
            int cursor_y = _point.y + y;
            int cursor_x = _point.x + x;
            int target_val = PackedInt32Array(metris[y])[x];
            current_state[cursor_y].set(cursor_x, target_val);
        }
    }
    
    return current_state;
}

void Tetris::reinit()
{
    state = _init_state();
}

Tetris::~Tetris()
{

}


Met Tetris::get_state() const { return state; }


Met Tetris::_init_state()
{
    Met result = Met();
    for (int y = 0; y < size.y; y+=1)
    {
        PackedInt32Array _arr = PackedInt32Array();
        for (int x = 0; x < size.x; x+=1)
            _arr.push_back(0);
        
        result.push_back(_arr);
    }

    return result;
}


bool Tetris::cast()
{
    // CODE

    return false;
}



TypedDictionary<String, Variant> Tetris::tick()
{
    // TypedArray<int64_t> indexes = search_completed_line();
    Met _state = cursor_merge_to_state();

    // return TypedDictionary<String, Variant> {
    //     {"state", _state}
    // };
    return {
        {"state", _state}
    };
}



Vector2i Tetris::get_size() const { return size; }
void Tetris::set_size(const Vector2i _size) {
    size = _size;
}

