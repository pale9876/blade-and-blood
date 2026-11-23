#pragma once


#include <godot_cpp/classes/physics_ray_query_parameters2d.hpp>
#include <godot_cpp/classes/physics_shape_query_parameters2d.hpp>
#include <godot_cpp/classes/node2d.hpp>


using namespace godot;


class Cast : public RefCounted
{
    GDCLASS (Cast, RefCounted)

    protected:
    static void _bind_methods();

    public:
    Dictionary cast_unit(
        const Vector2 point,
        Node2D &body,
        const int mask,
        TypedArray<RID> exclude
    );
};