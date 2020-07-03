#include "glwindow.h"
#include "mainwindow.h"
#include "course/course_1_1_1_hello_window.h"
#include "course/course_1_1_2_hello_window_clear.h"
#include "course/course_1_2_1_hello_triangle.h"
#include "course/course_1_2_2_hello_triangle_indexed.h"
#include "course/course_1_2_3_hello_triangle_exercise1.h"
#include "course/course_1_2_4_hello_triangle_exercise2.h"
#include "course/course_1_2_5_hello_triangle_exercise3.h"
#include "course/course_1_3_1_shaders_uniform.h"
#include "course/course_1_3_2_shaders_interpolation.h"
#include "course/course_1_4_1_textures.h"
#include "course/course_1_4_2_textures_combined.h"
#include "course/course_1_4_3_textures_exercise2.h"
#include "course/course_1_4_4_textures_exercise3.h"
#include "course/course_1_4_5_textures_exercise4.h"
#include "course/course_1_5_1_transformations.h"
#include "course/course_1_5_2_transformations_exercise2.h"
#include "course/course_1_6_1_coordinate_systems.h"
#include "course/course_1_6_2_coordinate_systems_depth.h"
#include "course/course_1_6_3_coordinate_systems_multiple.h"
#include "course/course_1_7_1_camera_circle.h"
#include "course/course_1_7_2_camera_keyboard_dt.h"
#include "course/course_1_7_3_camera_mouse_zoom.h"
#include "course/course_1_7_4_camera_class.h"
#include "course/course_2_1_1_colors.h"
#include "course/course_2_2_1_basic_lighting_diffuse.h"
#include "course/course_2_2_2_basic_lighting_specular.h"
#include "course/course_2_3_1_materials.h"
#include "course/course_2_3_2_materials_exercise1.h"
#include "course/course_2_4_1_lighting_maps_diffuse_map.h"
#include "course/course_2_4_2_lighting_maps_specular_map.h"
#include "course/course_2_4_4_lighting_maps_exercise4.h"
#include "course/course_2_5_1_light_casters_directional.h"
#include "course/course_2_5_2_light_casters_point.h"
#include "course/course_2_5_3_light_casters_spot.h"
#include "course/course_2_5_4_light_casters_spot_soft.h"
#include "course/course_2_6_1_multiple_lights.h"
#include "course/course_3_1_1_model_loading.h"
#include "course/course_4_1_1_depth_testing.h"
#include "course/course_4_1_2_depth_testing_view.h"
#include "course/course_4_2_1_stencil_testing.h"
#include "course/course_4_3_1_blending_discard.h"
#include "course/course_4_3_2_blending_sort.h"
#include "course/course_4_5_1_framebuffers.h"
#include "course/course_4_5_2_framebuffers_exercise1.h"
#include "course/course_4_6_1_cubemaps_skybox.h"
#include "course/course_4_6_2_cubemaps_environment_mapping.h"
#include "course/course_4_8_1_advanced_glsl_ubo.h"
#include "course/course_4_9_1_geometry_shader_house.h"
#include "course/course_4_9_2_geometry_shader_exploding.h"
#include "course/course_4_9_3_geometry_shader_normals.h"
#include "course/course_4_10_1_instancing_quads.h"
#include "course/course_4_10_2_asteroids.h"
#include "course/course_4_10_3_asteroids_instanced.h"
#include "course/course_4_11_1_anti_aliasing_msaa.h"
#include "course/course_4_11_2_anti_aliasing_offscreen.h"
#include "course/course_5_1_1_advanced_lighting.h"
#include "course/course_5_2_1_gamma_correction.h"
#include "course/course_5_3_1_1_shadow_mapping_depth.h"
#include "course/course_5_3_1_2_shadow_mapping_base.h"
#include "course/course_5_3_1_3_shadow_mapping.h"
#include "course/course_5_3_2_1_point_shadows.h"
#include "course/course_5_3_2_2_point_shadows_soft.h"
#include "course/course_5_4_1_normal_mapping.h"
#include "course/course_5_5_1_parallax_mapping.h"
#include "course/course_5_5_2_steep_parallax_mapping.h"
#include "course/course_5_5_3_parallax_occlusion_mapping.h"
#include "course/course_5_6_1_hdr.h"
#include "course/course_5_7_1_bloom.h"
#include "course/course_5_8_1_deferred_shading.h"
#include "course/course_5_8_2_deferred_shading_volumes.h"
#include "course/course_5_9_1_ssao.h"
#include "course/course_6_1_1_lighting.h"
#include "course/course_6_1_2_lighting_textured.h"
#include "course/course_6_2_1_1_ibl_irradiance_conversion.h"
#include "course/course_6_2_1_2_ibl_irradiance.h"
#include "course/course_6_2_2_1_ibl_specular.h"
#include "course/course_6_2_2_2_ibl_specular_textured.h"
#include "course/course_7_1_1_debugging.h"

GlWindow::GlWindow(MainWindow *mainWindow, QWidget *parent)
    :QOpenGLWidget(parent)
    ,mCourse(nullptr)
    ,mMainWindow(mainWindow)
{
    connect(mMainWindow, &MainWindow::courseTriggered, this, &GlWindow::renderCourse);
    connect(&mTimer, &QTimer::timeout, this, &GlWindow::renderFrame);
    mTimer.start(20);
}

GlWindow::~GlWindow()
{
}

void GlWindow::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void GlWindow::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void GlWindow::paintGL()
{
    if (mCourse != nullptr){
        mCourse->render();
    }
}

bool GlWindow::event(QEvent *event)
{
    if (event->type() == QEvent::Enter){
        this->setFocus();
        return true;
    }else if(event->type() == QEvent::Leave){
        this->clearFocus();
        return true;
    }

    return QOpenGLWidget::event(event);
}

void GlWindow::renderCourse(const QString &name)
{
    makeCurrent();
    if (mCourse){
        mMainWindow->setInspectorProxy(nullptr);
        delete mCourse;
        mCourse = nullptr;
    }

    if (name == "1_1_1"){
        mCourse = new Course_1_1_1_hello_window();
    }else if(name == "1_1_2"){
        mCourse = new Course_1_1_2_hello_window_clear();
    }else if(name == "1_2_1"){
        mCourse = new Course_1_2_1_hello_triangle();
    }else if(name == "1_2_2"){
        mCourse = new Course_1_2_2_hello_triangle_indexed();
    }else if(name == "1_2_3"){
        mCourse = new Course_1_2_3_hello_triangle_exercise1();
    }else if(name == "1_2_4"){
        mCourse = new Course_1_2_4_hello_triangle_exercise2();
    }else if(name == "1_2_5"){
        mCourse = new Course_1_2_5_hello_triangle_exercise3();
    }else if(name == "1_3_1"){
        mCourse = new Course_1_3_1_shaders_uniform();
    }else if(name == "1_3_2"){
        mCourse = new Course_1_3_2_shaders_interpolation();
    }else if(name == "1_4_1"){
        mCourse = new Course_1_4_1_textures();
    }else if(name == "1_4_2"){
        mCourse = new Course_1_4_2_textures_combined();
    }else if(name == "1_4_3"){
        mCourse = new Course_1_4_3_textures_exercise2();
    }else if(name == "1_4_4"){
        mCourse = new Course_1_4_4_textures_exercise3();
    }else if(name == "1_4_5"){
        mCourse = new Course_1_4_5_textures_exercise4();
    }else if(name == "1_5_1"){
        mCourse = new Course_1_5_1_transformations();
    }else if(name == "1_5_2"){
        mCourse = new Course_1_5_2_transformations_exercise2();
    }else if(name == "1_6_1"){
        mCourse = new Course_1_6_1_coordinate_systems();
    }else if(name == "1_6_2"){
        mCourse = new Course_1_6_2_coordinate_systems_depth();
    }else if(name == "1_6_3"){
        mCourse = new Course_1_6_3_coordinate_systems_multiple();
    }else if(name == "1_7_1"){
        mCourse = new Course_1_7_1_camera_circle();
    }else if(name == "1_7_2"){
        mCourse = new Course_1_7_2_camera_keyboard_dt();
    }else if(name == "1_7_3"){
        mCourse = new Course_1_7_3_camera_mouse_zoom();
    }else if(name == "1_7_4"){
        mCourse = new Course_1_7_4_camera_class();
    }else if(name == "2_1_1"){
        mCourse = new Course_2_1_1_colors();
    }else if(name == "2_2_1"){
        mCourse = new Course_2_2_1_basic_lighting_diffuse();
    }else if(name == "2_2_2"){
        mCourse = new Course_2_2_2_basic_lighting_specular();
    }else if(name == "2_3_1"){
        mCourse = new Course_2_3_1_materials();
    }else if(name == "2_3_2"){
        mCourse = new Course_2_3_2_materials_exercise1();
    }else if(name == "2_4_1"){
        mCourse = new Course_2_4_1_lighting_maps_diffuse_map();
    }else if(name == "2_4_2"){
        mCourse = new Course_2_4_2_lighting_maps_specular_map();
    }else if(name == "2_4_4"){
        mCourse = new Course_2_4_4_lighting_maps_exercises4();
    }else if(name == "2_5_1"){
        mCourse = new Course_2_5_1_light_casters_directional();
    }else if(name == "2_5_2"){
        mCourse = new Course_2_5_2_light_casters_point();
    }else if(name == "2_5_3"){
        mCourse = new Course_2_5_3_light_casters_spot();
    }else if(name == "2_5_4"){
        mCourse = new Course_2_5_4_light_casters_spot_soft();
    }else if(name == "2_6_1"){
        mCourse = new Course_2_6_1_multiple_lights();
    }else if(name == "3_1_1"){
        mCourse = new Course_3_1_1_model_loading();
    }else if(name == "4_1_1"){
        mCourse = new Course_4_1_1_depth_testing();
    }else if(name == "4_1_2"){
        mCourse = new Course_4_1_2_depth_testing_view();
    }else if(name == "4_2_1"){
        mCourse = new Course_4_2_1_stencil_testing();
    }else if(name == "4_3_1"){
        mCourse = new Course_4_3_1_blending_discard();
    }else if(name == "4_3_2"){
        mCourse = new Course_4_3_2_blending_sort();
    }else if(name == "4_5_1"){
        mCourse = new Course_4_5_1_framebuffers();
    }else if(name == "4_5_2"){
        mCourse = new Course_4_5_2_framebuffers_exercise1();
    }else if(name == "4_6_1"){
        mCourse = new Course_4_6_1_cubemaps_skybox();
    }else if(name == "4_6_2"){
        mCourse = new Course_4_6_2_cubemaps_environment_mapping();
    }else if(name == "4_8_1"){
        mCourse = new Course_4_8_1_advanced_glsl_ubo();
    }else if(name == "4_9_1"){
        mCourse = new Course_4_9_1_geometry_shader_house();
    }else if(name == "4_9_2"){
        mCourse = new Course_4_9_2_geometry_shader_exploding();
    }else if(name == "4_9_3"){
        mCourse = new Course_4_9_3_geometry_shader_normals();
    }else if(name == "4_10_1"){
        mCourse = new Course_4_10_1_instancing_quads();
    }else if(name == "4_10_2"){
        mCourse = new Course_4_10_2_asteroids();
    }else if(name == "4_10_3"){
        mCourse = new Course_4_10_3_asteroids_instanced();
    }else if(name == "4_11_1"){
        mCourse = new Course_4_11_1_anti_aliasing_msaa();
    }else if(name == "4_11_2"){
        mCourse = new Course_4_11_2_anti_aliasing_offscreen();
    }else if(name == "5_1_1"){
        mCourse = new Course_5_1_1_advanced_lighting();
    }else if(name == "5_2_1"){
        mCourse = new Course_5_2_1_gamma_correction();
    }else if(name == "5_3_1_1"){
        mCourse = new Course_5_3_1_1_shadow_mapping_depth();
    }else if(name == "5_3_1_2"){
        mCourse = new Course_5_3_1_2_shadow_mapping_base();
    }else if(name == "5_3_1_3"){
        mCourse = new Course_5_3_1_3_shadow_mapping();
    }else if(name == "5_3_2_1"){
        mCourse = new Course_5_3_2_1_point_shadows();
    }else if(name == "5_3_2_2"){
        mCourse = new Course_5_3_2_2_point_shadows_soft();
    }else if(name == "5_4_1"){
        mCourse = new Course_5_4_1_normal_mapping();
    }else if(name == "5_5_1"){
        mCourse = new Course_5_5_1_parallax_mapping();
    }else if(name == "5_5_2"){
        mCourse = new Course_5_5_2_steep_parallax_mapping();
    }else if(name == "5_5_3"){
        mCourse = new Course_5_5_3_parallax_occlusion_mapping();
    }else if(name == "5_6_1"){
        mCourse = new Course_5_6_1_hdr();
    }else if(name == "5_7_1"){
        mCourse = new Course_5_7_1_bloom();
    }else if(name == "5_8_1"){
        mCourse = new Course_5_8_1_deferred_shading();
    }else if(name == "5_8_2"){
        mCourse = new Course_5_8_2_deferred_shading_volumes();
    }else if(name == "5_9_1"){
        mCourse = new Course_5_9_1_ssao();
    }else if(name == "6_1_1"){
        mCourse = new Course_6_1_1_lighting();
    }else if(name == "6_1_2"){
        mCourse = new Course_6_1_2_lighting_textured();
    }else if(name == "6_2_1_1"){
        mCourse = new Course_6_2_1_1_ibl_irradiance_conversion();
    }else if(name == "6_2_1_2"){
        mCourse = new Course_6_2_1_2_ibl_irradiance();
    }else if(name == "6_2_2_1"){
        mCourse = new Course_6_2_2_1_ibl_specular();
    }else if(name == "6_2_2_2"){
        mCourse = new Course_6_2_2_2_ibl_specular_textured();
    }else if(name == "7_1_1"){
        mCourse = new Course_7_1_1_debugging();
    }


    if (mCourse != nullptr){
        mCourse->init(this);
        connect(mCourse, &Course::update, this, [this]{update();});
        connect(mCourse, &Course::propertyChanged, this, &GlWindow::updateInspectorProperty);
    }

    this->update();
    mMainWindow->setInspectorProxy(mCourse);
}

void GlWindow::updateInspectorProperty(const QString &propertyId, const QVariant &value)
{
    mMainWindow->setInspectorProperty(propertyId, value);
}

void GlWindow::renderFrame()
{
    this->update();
}
