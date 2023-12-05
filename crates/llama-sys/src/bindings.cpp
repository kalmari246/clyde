#include <clip.h>
#include <ggml-opencl.h>
#include <llama.h>
#include <sampling.h>

/// Library
extern "C" void bindings_init(bool numa_aware) {
    llama_backend_init(numa_aware);
}

// CLIP model
extern "C" void *bindings_clip_model_open(const char *path, const int verbosity_level) {
    return static_cast<void *>(clip_model_load(path, verbosity_level));
}

extern "C" void bindings_clip_model_drop(void *model) {
    clip_free(static_cast<clip_ctx *>(model));
}

// CLIP image
extern "C" bool bindings_clip_image_encode(const void *model, const int threads, void *image, float *buf) {
    return clip_image_encode(static_cast<const clip_ctx *>(model), threads, static_cast<struct clip_image_f32 *>(image), buf);
}

extern "C" bool bindings_clip_image_batch_encode(const void *model, const int threads, void *images, float *buf) {
    return clip_image_batch_encode(static_cast<const clip_ctx *>(model), threads, static_cast<struct clip_image_f32_batch *>(images), buf);
}

// Model
extern "C" void *bindings_model_open(const char *path, const void *options) {
    return static_cast<void *>(llama_load_model_from_file(path, *static_cast<const llama_model_params *>(options)));
}

extern "C" void bindings_model_drop(void *model) {
    llama_free_model(static_cast<llama_model *>(model));
}

// Model options
extern "C" void *bindings_model_options_new() {
    return static_cast<void *>(new llama_model_params(llama_model_default_params()));
}

extern "C" uint16_t bindings_model_options_gpu_layers(const void *options) {
    return static_cast<uint16_t>(static_cast<const llama_model_params *>(options)->n_gpu_layers);
}

extern "C" void bindings_model_options_set_gpu_layers(void *options, const uint16_t value) {
    static_cast<llama_model_params *>(options)->n_gpu_layers = static_cast<int32_t>(value);
}

extern "C" bool bindings_model_options_use_mlock(const void *options) {
    return static_cast<const llama_model_params *>(options)->use_mlock;
}

extern "C" void bindings_model_options_set_use_mlock(void *options, const bool value) {
    static_cast<llama_model_params *>(options)->use_mlock = value;
}

extern "C" bool bindings_model_options_use_mmap(const void *options) {
    return static_cast<const llama_model_params *>(options)->use_mmap;
}

extern "C" void bindings_model_options_set_use_mmap(void *options, const bool value) {
    static_cast<llama_model_params *>(options)->use_mmap = value;
}

extern "C" void bindings_model_options_drop(void *options) {
    delete static_cast<llama_model_params *>(options);
}

// Session
extern "C" void *bindings_session_new(void *model, const void *options) {
    return static_cast<void *>(llama_new_context_with_model(static_cast<llama_model *>(model), *static_cast<const llama_context_params *>(options)));
}

extern "C" void bindings_session_drop(void *session) {
    static_cast<llama_context *>(session);
}

// Session options
extern "C" void *bindings_session_options_new() {
    return static_cast<void *>(new llama_context_params(llama_context_default_params()));
}

extern "C" void bindings_session_options_drop(void *options) {
    delete static_cast<llama_context_params *>(options);
}

// Session sampling
extern "C" void *bindings_session_sampling_new(const void *options) {
    return static_cast<void *>(llama_sampling_init(*static_cast<const struct llama_sampling_params *>(options)));
}

extern "C" void bindings_session_sampling_reset(void *sampling) {
    llama_sampling_reset(static_cast<llama_sampling_context *>(sampling));
}

extern "C" void bindings_session_sampling_drop(void *sampling) {
    llama_sampling_free(static_cast<llama_sampling_context *>(sampling));
}

// Session sampling options
extern "C" void *bindings_session_sampling_options_new() {
    return static_cast<void *>(new llama_sampling_params);   
}

extern "C" float bindings_session_sampling_options_temperature(const void *options) {
    return static_cast<const llama_sampling_params *>(options)->temp;
}

extern "C" void bindings_session_sampling_options_set_temperature(void *options, const float value) {
    static_cast<llama_sampling_params *>(options)->temp = value;
}

extern "C" float bindings_session_sampling_options_top_k(const void *options) {
    return static_cast<const llama_sampling_params *>(options)->top_k;
}

extern "C" void bindings_session_sampling_options_set_top_k(void *options, const float value) {
    static_cast<llama_sampling_params *>(options)->top_k = value;
}

extern "C" float bindings_session_sampling_options_top_p(const void *options) {
    return static_cast<const llama_sampling_params *>(options)->top_p;
}

extern "C" void bindings_session_sampling_options_set_top_p(void *options, const float value) {
    static_cast<llama_sampling_params *>(options)->top_p = value;
}

extern "C" void bindings_session_sampling_options_drop(void *options) {
    delete static_cast<llama_sampling_params *>(options);
}
