set(src_dirs        
    .
    src
)

set(include_dirs      
    .
    include
)

idf_component_register(
    SRC_DIRS ${src_dirs} 
    INCLUDE_DIRS ${include_dirs}
)