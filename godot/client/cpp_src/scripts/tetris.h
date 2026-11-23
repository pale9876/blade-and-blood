#pragma once


#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/typed_dictionary.hpp>
#include "block.h"


using namespace godot;


// typedef
typedef PackedInt32Array Line;
typedef TypedArray<PackedInt32Array> Met;
typedef TypedArray<Vector2i> Coords;


class Tetris : public Node
{
    GDCLASS (Tetris, Node)

    const Vector2i DEFAULT_SIZE = Vector2i(10, 20);

    private:
    Met state;

    Block* _prev  = nullptr;
    Block* cursor = nullptr;
        
    TypedDictionary<String, Variant> tick();
    bool cast();
    bool cast_point(Met _rotated_preview);

    
    void init_cursor(Block* _block) {
        if (_block == nullptr) return;

        if (cursor != nullptr)
        {
            // cursor -> queue_free();
            call_deferred("remove_child", cursor);
            cursor->call_deferred("queue_free", cursor);
            cursor = nullptr;
        }

        this->cursor = _block;
        this->call_deferred("add_child", _block);
    }


    void init_prev(Block* _block)
    {
        if (_block == nullptr) return;

        if (_prev != nullptr)
        {
            call_deferred("remove_child", _prev);
            _prev->call_deferred("queue_free", _prev);
            _prev = nullptr;
        }

        this->_prev = _block;
        this->call_deferred("add_child", _block);
    }



    Block* get_cursor() { return this->cursor; }
    Block* get_prev() { return this->_prev; }

    TypedArray<int64_t> search_completed_line()
    {
        TypedArray<int64_t> result = {};

        for (int i = 0; i < state.size(); i++)
        {
            PackedInt32Array line_state = state[i];
            if (is_completed_line(line_state))
                result.push_back(i);
        }

        return result;
    }
    
    bool is_completed_line(PackedInt32Array &_line)
    {
        for (auto &&i : _line)
            if (i == 0) return false;
        
        return true;
    }

    bool intrude_top_row()
    {
        PackedInt32Array _topline = this->state[0];
        for (int i = 0; i < _topline.size(); i+=1)
        {
            if (_topline[i] == 1)
                return true;
        }

        return false;
    }

    bool state_is_dead()
    {
        PackedInt32Array _topline = this->state[0];
        return !is_completed_line(_topline) && intrude_top_row();
    }
    
    void pull_lines(int from_line_idx)
    {
        for (int i = from_line_idx; i < 2; i-=1)
        {
            PackedInt32Array _cursor = state[i];
            PackedInt32Array top_line = state[i - 1];
            state[i] = top_line;
        }
    }


    Met cursor_merge_to_state();

    void cursor_move_down(Block &block, bool test = false);
    void cursor_move_left(Block &block, bool test = false);
    void cursor_move_right(Block &block, bool test = false);

    Met _init_state();
        
    protected:
    static void _bind_methods();
        
    public:
    Vector2i size;

    Tetris();
    ~Tetris();

    // Methods
    void _enter_tree() override;
    void reinit();

    Met get_state() const;

    Vector2i get_size() const;
    void set_size(const Vector2i _size);
    void resize(const Vector2i _size){
        this->set_size(_size);
        reinit();
    }
        
    void set_time_scale(const double time_scale);
    static Coords coordinated(Met &metris);
    static Met Mapping(Vector2i coord, Coords _origin, Met state);

};


