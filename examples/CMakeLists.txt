add_executable(example
example.cpp
)

target_compile_features(example PUBLIC cxx_std_20)
target_link_libraries(example ce)
