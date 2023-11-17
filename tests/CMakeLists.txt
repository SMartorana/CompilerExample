add_executable(test
test.cpp
)

target_compile_features(test PUBLIC cxx_std_20)
target_link_libraries(test ce catch)
