QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS QT_DISABLE_DEPRECATED_BEFORE=0

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    course/course.cpp \
    course/course_1_1_1_hello_window.cpp \
    course/course_1_1_2_hello_window_clear.cpp \
    course/course_1_2_1_hello_triangle.cpp \
    course/course_1_2_2_hello_triangle_indexed.cpp \
    course/course_1_2_3_hello_triangle_exercise1.cpp \
    course/course_1_2_4_hello_triangle_exercise2.cpp \
    course/course_1_2_5_hello_triangle_exercise3.cpp \
    course/course_1_3_1_shaders_uniform.cpp \
    course/course_1_3_2_shaders_interpolation.cpp \
    course/course_1_4_1_textures.cpp \
    course/course_1_4_2_textures_combined.cpp \
    course/course_1_4_3_textures_exercise2.cpp \
    course/course_1_4_4_textures_exercise3.cpp \
    course/course_1_4_5_textures_exercise4.cpp \
    course/course_1_5_1_transformations.cpp \
    course/course_1_5_2_transformations_exercise2.cpp \
    course/course_1_6_1_coordinate_systems.cpp \
    course/course_1_6_2_coordinate_systems_depth.cpp \
    course/course_1_6_3_coordinate_systems_multiple.cpp \
    course/course_1_7_1_camera_circle.cpp \
    course/course_1_7_2_camera_keyboard_dt.cpp \
    course/course_1_7_3_camera_mouse_zoom.cpp \
    course/course_1_7_4_camera_class.cpp \
    course/course_2_1_1_colors.cpp \
    course/course_2_2_1_basic_lighting_diffuse.cpp \
    course/course_2_2_2_basic_lighting_specular.cpp \
    course/course_2_3_1_materials.cpp \
    course/course_2_3_2_materials_exercise1.cpp \
    course/course_2_4_1_lighting_maps_diffuse_map.cpp \
    course/course_2_4_2_lighting_maps_specular_map.cpp \
    course/course_2_4_4_lighting_maps_exercise4.cpp \
    course/course_2_5_1_light_casters_directional.cpp \
    course/course_2_5_2_light_casters_point.cpp \
    course/course_2_5_3_light_casters_spot.cpp \
    course/course_2_5_4_light_casters_spot_soft.cpp \
    course/course_2_6_1_multiple_lights.cpp \
    course/course_3_1_1_model_loading.cpp \
    course/course_4_10_1_instancing_quads.cpp \
    course/course_4_10_2_asteroids.cpp \
    course/course_4_10_3_asteroids_instanced.cpp \
    course/course_4_11_1_anti_aliasing_msaa.cpp \
    course/course_4_11_2_anti_aliasing_offscreen.cpp \
    course/course_4_1_1_depth_testing.cpp \
    course/course_4_1_2_depth_testing_view.cpp \
    course/course_4_2_1_stencil_testing.cpp \
    course/course_4_3_1_blending_discard.cpp \
    course/course_4_3_2_blending_sort.cpp \
    course/course_4_5_1_framebuffers.cpp \
    course/course_4_5_2_framebuffers_exercise1.cpp \
    course/course_4_6_1_cubemaps_skybox.cpp \
    course/course_4_6_2_cubemaps_environment_mapping.cpp \
    course/course_4_8_1_advanced_glsl_ubo.cpp \
    course/course_4_9_1_geometry_shader_house.cpp \
    course/course_4_9_2_geometry_shader_exploding.cpp \
    course/course_4_9_3_geometry_shader_normals.cpp \
    course/course_5_1_1_advanced_lighting.cpp \
    course/course_5_2_1_gamma_correction.cpp \
    course/course_5_3_1_1_shadow_mapping_depth.cpp \
    course/course_5_3_1_2_shadow_mapping_base.cpp \
    course/course_5_3_1_3_shadow_mapping.cpp \
    course/course_5_3_2_1_point_shadows.cpp \
    course/course_5_3_2_2_point_shadows_soft.cpp \
    course/course_5_4_1_normal_mapping.cpp \
    course/course_5_5_1_parallax_mapping.cpp \
    course/course_5_5_2_steep_parallax_mapping.cpp \
    course/course_5_5_3_parallax_occlusion_mapping.cpp \
    course/course_5_6_1_hdr.cpp \
    course/course_5_7_1_bloom.cpp \
    course/course_5_8_1_deferred_shading.cpp \
    course/course_5_8_2_deferred_shading_volumes.cpp \
    course/course_5_9_1_ssao.cpp \
    course/course_6_1_1_lighting.cpp \
    course/course_6_1_2_lighting_textured.cpp \
    course/course_6_2_1_1_ibl_irradiance_conversion.cpp \
    course/course_6_2_1_2_ibl_irradiance.cpp \
    course/course_6_2_2_1_ibl_specular.cpp \
    course/course_6_2_2_2_ibl_specular_textured.cpp \
    course/course_7_1_1_debugging.cpp \
    course/coursewithcamera.cpp \
    glwindow.cpp \
    inspector/inspector.cpp \
    inspector/inspectordockwidget.cpp \
    inspector/inspectorproxy.cpp \
    inspector/inspectorproxyexample.cpp \
    main.cpp \
    mainwindow.cpp \
    mydockwidget.cpp \
    property/matrixeditor.cpp \
    property/qtbuttonpropertybrowser.cpp \
    property/qteditorfactory.cpp \
    property/qtgroupboxpropertybrowser.cpp \
    property/qtpropertybrowser.cpp \
    property/qtpropertybrowserutils.cpp \
    property/qtpropertymanager.cpp \
    property/qttreepropertybrowser.cpp \
    property/qtvariantproperty.cpp \
    stb_image.cpp

HEADERS += \
    assimp/BaseImporter.h \
    assimp/Bitmap.h \
    assimp/BlobIOSystem.h \
    assimp/ByteSwapper.h \
    assimp/Compiler/poppack1.h \
    assimp/Compiler/pstdint.h \
    assimp/Compiler/pushpack1.h \
    assimp/CreateAnimMesh.h \
    assimp/DefaultIOStream.h \
    assimp/DefaultIOSystem.h \
    assimp/DefaultLogger.hpp \
    assimp/Defines.h \
    assimp/Exceptional.h \
    assimp/Exporter.hpp \
    assimp/GenericProperty.h \
    assimp/Hash.h \
    assimp/IOStream.hpp \
    assimp/IOStreamBuffer.h \
    assimp/IOSystem.hpp \
    assimp/Importer.hpp \
    assimp/LineSplitter.h \
    assimp/LogAux.h \
    assimp/LogStream.hpp \
    assimp/Logger.hpp \
    assimp/Macros.h \
    assimp/MathFunctions.h \
    assimp/MemoryIOWrapper.h \
    assimp/NullLogger.hpp \
    assimp/ParsingUtils.h \
    assimp/Profiler.h \
    assimp/ProgressHandler.hpp \
    assimp/RemoveComments.h \
    assimp/SGSpatialSort.h \
    assimp/SceneCombiner.h \
    assimp/SkeletonMeshBuilder.h \
    assimp/SmoothingGroups.h \
    assimp/SmoothingGroups.inl \
    assimp/SpatialSort.h \
    assimp/StandardShapes.h \
    assimp/StreamReader.h \
    assimp/StreamWriter.h \
    assimp/StringComparison.h \
    assimp/StringUtils.h \
    assimp/Subdivision.h \
    assimp/TinyFormatter.h \
    assimp/Vertex.h \
    assimp/XMLTools.h \
    assimp/ZipArchiveIOSystem.h \
    assimp/aabb.h \
    assimp/ai_assert.h \
    assimp/anim.h \
    assimp/camera.h \
    assimp/cexport.h \
    assimp/cfileio.h \
    assimp/cimport.h \
    assimp/color4.h \
    assimp/color4.inl \
    assimp/config.h \
    assimp/defs.h \
    assimp/fast_atof.h \
    assimp/importerdesc.h \
    assimp/irrXMLWrapper.h \
    assimp/light.h \
    assimp/material.h \
    assimp/material.inl \
    assimp/matrix3x3.h \
    assimp/matrix3x3.inl \
    assimp/matrix4x4.h \
    assimp/matrix4x4.inl \
    assimp/mesh.h \
    assimp/metadata.h \
    assimp/pbrmaterial.h \
    assimp/port/AndroidJNI/AndroidJNIIOSystem.h \
    assimp/postprocess.h \
    assimp/qnan.h \
    assimp/quaternion.h \
    assimp/quaternion.inl \
    assimp/scene.h \
    assimp/texture.h \
    assimp/types.h \
    assimp/vector2.h \
    assimp/vector2.inl \
    assimp/vector3.h \
    assimp/vector3.inl \
    assimp/version.h \
    core/camera.h \
    core/mesh.h \
    core/model.h \
    course/course.h \
    course/course_1_1_1_hello_window.h \
    course/course_1_1_2_hello_window_clear.h \
    course/course_1_2_1_hello_triangle.h \
    course/course_1_2_2_hello_triangle_indexed.h \
    course/course_1_2_3_hello_triangle_exercise1.h \
    course/course_1_2_4_hello_triangle_exercise2.h \
    course/course_1_2_5_hello_triangle_exercise3.h \
    course/course_1_3_1_shaders_uniform.h \
    course/course_1_3_2_shaders_interpolation.h \
    course/course_1_4_1_textures.h \
    course/course_1_4_2_textures_combined.h \
    course/course_1_4_3_textures_exercise2.h \
    course/course_1_4_4_textures_exercise3.h \
    course/course_1_4_5_textures_exercise4.h \
    course/course_1_5_1_transformations.h \
    course/course_1_5_2_transformations_exercise2.h \
    course/course_1_6_1_coordinate_systems.h \
    course/course_1_6_2_coordinate_systems_depth.h \
    course/course_1_6_3_coordinate_systems_multiple.h \
    course/course_1_7_1_camera_circle.h \
    course/course_1_7_2_camera_keyboard_dt.h \
    course/course_1_7_3_camera_mouse_zoom.h \
    course/course_1_7_4_camera_class.h \
    course/course_2_1_1_colors.h \
    course/course_2_2_1_basic_lighting_diffuse.h \
    course/course_2_2_2_basic_lighting_specular.h \
    course/course_2_3_1_materials.h \
    course/course_2_3_2_materials_exercise1.h \
    course/course_2_4_1_lighting_maps_diffuse_map.h \
    course/course_2_4_2_lighting_maps_specular_map.h \
    course/course_2_4_4_lighting_maps_exercise4.h \
    course/course_2_5_1_light_casters_directional.h \
    course/course_2_5_2_light_casters_point.h \
    course/course_2_5_3_light_casters_spot.h \
    course/course_2_5_4_light_casters_spot_soft.h \
    course/course_2_6_1_multiple_lights.h \
    course/course_3_1_1_model_loading.h \
    course/course_4_10_1_instancing_quads.h \
    course/course_4_10_2_asteroids.h \
    course/course_4_10_3_asteroids_instanced.h \
    course/course_4_11_1_anti_aliasing_msaa.h \
    course/course_4_11_2_anti_aliasing_offscreen.h \
    course/course_4_1_1_depth_testing.h \
    course/course_4_1_2_depth_testing_view.h \
    course/course_4_2_1_stencil_testing.h \
    course/course_4_3_1_blending_discard.h \
    course/course_4_3_2_blending_sort.h \
    course/course_4_5_1_framebuffers.h \
    course/course_4_5_2_framebuffers_exercise1.h \
    course/course_4_6_1_cubemaps_skybox.h \
    course/course_4_6_2_cubemaps_environment_mapping.h \
    course/course_4_8_1_advanced_glsl_ubo.h \
    course/course_4_9_1_geometry_shader_house.h \
    course/course_4_9_2_geometry_shader_exploding.h \
    course/course_4_9_3_geometry_shader_normals.h \
    course/course_5_1_1_advanced_lighting.h \
    course/course_5_2_1_gamma_correction.h \
    course/course_5_3_1_1_shadow_mapping_depth.h \
    course/course_5_3_1_2_shadow_mapping_base.h \
    course/course_5_3_1_3_shadow_mapping.h \
    course/course_5_3_2_1_point_shadows.h \
    course/course_5_3_2_2_point_shadows_soft.h \
    course/course_5_4_1_normal_mapping.h \
    course/course_5_5_1_parallax_mapping.h \
    course/course_5_5_2_steep_parallax_mapping.h \
    course/course_5_5_3_parallax_occlusion_mapping.h \
    course/course_5_6_1_hdr.h \
    course/course_5_7_1_bloom.h \
    course/course_5_8_1_deferred_shading.h \
    course/course_5_8_2_deferred_shading_volumes.h \
    course/course_5_9_1_ssao.h \
    course/course_6_1_1_lighting.h \
    course/course_6_1_2_lighting_textured.h \
    course/course_6_2_1_1_ibl_irradiance_conversion.h \
    course/course_6_2_1_2_ibl_irradiance.h \
    course/course_6_2_2_1_ibl_specular.h \
    course/course_6_2_2_2_ibl_specular_textured.h \
    course/course_7_1_1_debugging.h \
    course/coursewithcamera.h \
    glwindow.h \
    inspector/inspector.h \
    inspector/inspectordockwidget.h \
    inspector/inspectorproxy.h \
    inspector/inspectorproxyexample.h \
    mainwindow.h \
    mydockwidget.h \
    property/matrixeditor.h \
    property/qtbuttonpropertybrowser.h \
    property/qteditorfactory.h \
    property/qtgroupboxpropertybrowser.h \
    property/qtpropertybrowser.h \
    property/qtpropertybrowserutils_p.h \
    property/qtpropertymanager.h \
    property/qttreepropertybrowser.h \
    property/qtvariantproperty.h \
    stb_image.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

#win32:LIBS += -lOpengl32 \
#                         -lglu32


#构建完成后,拷贝shaders和resource目录下的资源到exe目录
install.path = $$OUT_PWD
install.files += shaders
install.files += resources

INSTALLS += \
    install

DISTFILES += \
    assimp/.editorconfig \
    assimp/config.h.in


win32: LIBS += -L$$PWD/./ -lassimp-vc141-mt

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/./assimp-vc141-mt.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/./libassimp-vc141-mt.a

win32:LIBS += -lOpengl32 \
                         -lglu32
