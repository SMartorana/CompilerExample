add_executable(example
example.cpp
)
add_executable(complex-example
complex-example.cpp
)

target_compile_features(example PUBLIC cxx_std_20)
target_link_libraries(example ce)

target_compile_features(complex-example PUBLIC cxx_std_20)
target_link_libraries(complex-example ce)
