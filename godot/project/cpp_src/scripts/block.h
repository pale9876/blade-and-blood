#pragma once


#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/packed_int32_array.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;


// TypeDef
typedef TypedArray<PackedInt32Array> Met;


class Block : public Node
{
    GDCLASS(Block, Node)
    
    protected:
    static void _bind_methods();
    
    public:
    enum Type {
        SQUARE = 0,
        L = 1,
        I = 2,
        Z = 3,
        REVERSE_Z= 4,
    };
    
    void _enter_tree() override;
    
    virtual void rotate();
    virtual TypedArray<PackedInt32Array> get_shape(int state);
    
    
    Type get_rand_type();
    static Block* create_block(const int type);
    static int block_pick_random()
    {
        Ref<RandomNumberGenerator> rand = memnew(RandomNumberGenerator);
        int result = rand->randi_range(0, 5);
        return result;
    }
    
    TypedArray<PackedInt32Array> metris = {};
    Vector2i coord = Vector2i();
    
    Block();
    ~Block();
    
    private:

};

VARIANT_ENUM_CAST(Block::Type);



class IBlock : public Block
{
    GDCLASS(IBlock, Block)

    
    protected:
    static void _bind_methods();
    
    public:
    void rotate() override;
    
    enum State {
        ㅣ,
        ㅡ,
    };
    
    IBlock();
    ~IBlock();
};


VARIANT_ENUM_CAST(IBlock::State);


class LBlock : public Block
{
    GDCLASS(LBlock, Block)

    protected:
    static void _bind_methods();

    public:
    enum State {
        _0 = 0,
        _90 = 1,
        _180 = 2,
        _270 = 3,
    };

    State state = State::_0;

    void rotate() override;
    TypedArray<PackedInt32Array> get_shape(int state) override;

    LBlock();
    ~LBlock();
};



class Square : public Block
{
    GDCLASS(Square, Block)
    private:

    protected:
    static void _bind_methods();

    public:
    void rotate() override;
        
    Square();
    ~Square();

};


class ZBlock : public Block
{
    GDCLASS(ZBlock, Block)
    
    protected:
    static void _bind_methods();

    public:
    ZBlock();
    ~ZBlock();

    void rotate() override;
};


class ReverseZBlock: public Block
{
    GDCLASS(ReverseZBlock, Block)

    protected:
    static void _bind_methods();

    public:
    ReverseZBlock();
    ~ReverseZBlock();
};