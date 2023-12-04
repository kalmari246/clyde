use std::env;

fn main() {
    let mut c = cc::Build::new();
    let mut cxx = cc::Build::new();

    c.file("../../subprojects/llama.cpp/ggml-alloc.c")
        .file("../../subprojects/llama.cpp/ggml-backend.c")
        .file("../../subprojects/llama.cpp/ggml.c")
        .file("../../subprojects/llama.cpp/ggml-quants.c")
        .include("../../subprojects/llama.cpp");

    cxx.cpp(true)
        .file("src/bindings.cpp")
        .file("../../subprojects/llama.cpp/llama.cpp")
        .include("../../subprojects/llama.cpp")
        .include("../../subprojects/llama.cpp/common")
        .include("../../subprojects/llama.cpp/examples/llava");

    if env::var_os("CARGO_FEATURE_CLBLAST").is_some() {
        println!("cargo:rustc-link-lib=clblast");
        println!("cargo:rustc-link-lib=OpenCL");

        cxx.define("GGML_USE_CLBLAST", "1")
            .file("../../subprojects/llama.cpp/ggml-opencl.cpp");
    } else if env::var_os("CARGO_FEATURE_CUBLAS").is_some() {
        println!("cargo:rustc-link-lib=cublas");
    } else if env::var_os("CARGO_FEATURE_HIPBLAST").is_some() {
        println!("cargo:rustc-link-lib=hipblast");
    }

    c.compile("bindings-c");
    cxx.compile("bindings-cxx");
}