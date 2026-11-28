#include "block.h"
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/class_db.hpp>



using namespace godot;


void Block::_bind_methods()
{

    // Enum
    BIND_ENUM_CONSTANT(SQUARE);
    BIND_ENUM_CONSTANT(L);
    BIND_ENUM_CONSTANT(I);
    BIND_ENUM_CONSTANT(Z);
    BIND_ENUM_CONSTANT(REVERSE_Z);
    
    // Static
    ClassDB::bind_static_method(get_class_static(), D_METHOD("create_block", "type"), &Block::create_block);
    ClassDB::bind_static_method(get_class_static(), D_METHOD("block_pick_random"), &Block::block_pick_random);
    
    // Signal
    ClassDB::add_signal(get_class_static(), MethodInfo("shape_changed"));
}


Block* Block::create_block(const int type)
{
    switch (type)
    {
        case Block::I:
            return memnew(IBlock);
        
        case Block::L:
            return memnew(LBlock);
        
        case Block::SQUARE:
            return memnew(Square);
        
        case Block::Z:
            return memnew(ZBlock);
        
        case Block::REVERSE_Z:
            return memnew(ReverseZBlock);
    }

    return memnew(Block);
}


void Block::rotate()
{
    
}

TypedArray<PackedInt32Array> Block::get_shape(int state)
{
    return {};
}


Block::Block()
{
    if (!Engine::get_singleton() -> is_editor_hint())
    {
        // _timer = memnew(Timer);
        // _timer -> connect("timeout", Callable(this, "_timeout"));
        // add_child(_timer);
    }
}


void Block::_enter_tree()
{
    
}

Block::~Block()
{
    
}



// IBlock
void IBlock::_bind_methods()
{
    BIND_ENUM_CONSTANT(ㅣ);
    BIND_ENUM_CONSTANT(ㅡ);
}

IBlock::IBlock()
{
    this->coord = Vector2i();
    this->metris = {
        PackedInt32Array({1,0,0,0}),
        PackedInt32Array({1,0,0,0}),
        PackedInt32Array({1,0,0,0}),
        PackedInt32Array({1,0,0,0})
    };
}

void IBlock::rotate()
{
    
}


IBlock::~IBlock()
{
    
}


// LBlock

void LBlock::_bind_methods()
{

}


void LBlock::rotate()
{
    this->metris = {
        PackedInt32Array({0,0,0,0}),
        PackedInt32Array({1,0,0,0}),
        PackedInt32Array({1,0,0,0}),
        PackedInt32Array({1,1,0,0})
    };
    state = (State)((int)state + 1);
    metris = get_shape((int)state);
    emit_signal("shape_changed", this);
}


TypedArray<PackedInt32Array> LBlock::get_shape(int state)
{
    TypedArray<PackedInt32Array> result = {};

    switch (State(state))
    {
        case _0:
            result = {
                PackedInt32Array({1,0,0,0}),
                PackedInt32Array({1,0,0,0}),
                PackedInt32Array({1,1,0,0}),
                PackedInt32Array({0,0,0,0})
            };
        case _90:
            result = {
                PackedInt32Array({0,0,0,0}),
                PackedInt32Array({1,1,1,0}),
                PackedInt32Array({1,0,0,0}),
                PackedInt32Array({0,0,0,0})
            };
        case _180:
            result = {
                PackedInt32Array({0,0,0,0}),
                PackedInt32Array({1,1,0,0}),
                PackedInt32Array({0,1,0,0}),
                PackedInt32Array({0,1,0,0})
            };
        case _270:
            result = {
                PackedInt32Array({0,0,0,0}),
                PackedInt32Array({0,0,1,0}),
                PackedInt32Array({1,1,1,0}),
                PackedInt32Array({0,0,0,0})
            };
    }

    return {};
}


LBlock::LBlock(){
    state = State::_0;
    metris = get_shape((int)state);
}
LBlock::~LBlock(){}



// Square
void Square::_bind_methods(){}
void Square::rotate(){}

Square::Square(){
    this->metris = {
        PackedInt32Array({1,1}),
        PackedInt32Array({1,1})
    };
}
Square::~Square(){}


// ZBlock
void ZBlock::_bind_methods(){}
void ZBlock::rotate(){}

ZBlock::ZBlock(){}
ZBlock::~ZBlock(){}



// ReverseZBlock

void ReverseZBlock::_bind_methods(){}

ReverseZBlock::ReverseZBlock(){}
ReverseZBlock::~ReverseZBlock(){}