# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "child",
    srcs = ["child1.c"],
)

cc_binary(
    name = "hello",
    srcs = ["main.c"],
    deps = [
        ":child",
        "//child2:child2",
        ],
)