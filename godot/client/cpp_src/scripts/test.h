#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/window.hpp>


namespace godot{
    class ChaosExample : public Node
    {
        GDCLASS (ChaosExample, Node)
        
        private:
        // static void _add_property(Variant::Type _type, String _name, PropertyHint hint, String hint_string);

        protected:
        static void _bind_methods();

        public:
        ChaosExample();
        ~ChaosExample();
    };
};
