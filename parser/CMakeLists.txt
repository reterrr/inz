add_library(parser_obj
        OBJECT
        main.cpp
        expr.hpp entity.hpp entity_type.hpp
        compound.hpp
        compound_type.hpp
        node.cpp
        node.hpp
        ../ast/qual.hpp
)
