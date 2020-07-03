#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QMenu>
#include <QSplitter>
#include <QScrollArea>
#include "mydockwidget.h"
#include "property/matrixeditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSplitter *spliter = new QSplitter(this);

    QMenu *courseMenu = new QMenu(tr("Course"),this);
    ui->menubar->addMenu(courseMenu);

    QMenu *testMenu = new QMenu(tr("Test"),this);
    ui->menubar->addMenu(testMenu);

    QAction *inspectExample2 = new QAction(tr("inspect example2"));
    testMenu->addAction(inspectExample2);
    connect(inspectExample2,&QAction::triggered,this,&MainWindow::actionTriggered_inspect_example2);
    QAction *uninspectExample2 = new QAction(tr("uninspect example2"));
    testMenu->addAction(uninspectExample2);
    connect(uninspectExample2,&QAction::triggered,this,&MainWindow::actionTriggered_uninspect_example2);
    QAction *showMatrix = new QAction(tr("show matrix"));
    testMenu->addAction(showMatrix);
    connect(showMatrix,&QAction::triggered,this,&MainWindow::actionTriggered_showMatrix);

    QMenu *subMenu1 = new QMenu(tr("1.getting_started"),this);
    courseMenu->addMenu(subMenu1);

    QAction *action_1_1_1 = new QAction(tr("1.1.hello_window"));
    subMenu1->addAction(action_1_1_1);
    connect(action_1_1_1, &QAction::triggered, this, [this]{emit courseTriggered("1_1_1");});

    QAction *action_1_1_2 = new QAction(tr("1.2.hello_window_clear"));
    subMenu1->addAction(action_1_1_2);
    connect(action_1_1_2, &QAction::triggered, this, [this]{emit courseTriggered("1_1_2");});

    QAction *action_1_2_1 = new QAction(tr("2.1.hello_triangle"));
    subMenu1->addAction(action_1_2_1);
    connect(action_1_2_1, &QAction::triggered, this, [this]{emit courseTriggered("1_2_1");});

    QAction *action_1_2_2 = new QAction(tr("2.2.hello_triangle_indexed"));
    subMenu1->addAction(action_1_2_2);
    connect(action_1_2_2, &QAction::triggered, this, [this]{emit courseTriggered("1_2_2");});

    QAction *action_1_2_3 = new QAction(tr("2.3.hello_triangle_exercise1"));
    subMenu1->addAction(action_1_2_3);
    connect(action_1_2_3, &QAction::triggered, this, [this]{emit courseTriggered("1_2_3");});

    QAction *action_1_2_4 = new QAction(tr("2.4.hello_triangle_exercise2"));
    subMenu1->addAction(action_1_2_4);
    connect(action_1_2_4, &QAction::triggered, this, [this]{emit courseTriggered("1_2_4");});

    QAction *action_1_2_5 = new QAction(tr("2.5.hello_triangle_exercise3"));
    subMenu1->addAction(action_1_2_5);
    connect(action_1_2_5, &QAction::triggered, this, [this]{emit courseTriggered("1_2_5");});

    QAction *action_1_3_1 = new QAction(tr("3.1.shaders_uniform"));
    subMenu1->addAction(action_1_3_1);
    connect(action_1_3_1, &QAction::triggered, this, [this]{emit courseTriggered("1_3_1");});

    QAction *action_1_3_2 = new QAction(tr("3.2.shaders_interpolation"));
    subMenu1->addAction(action_1_3_2);
    connect(action_1_3_2, &QAction::triggered, this, [this]{emit courseTriggered("1_3_2");});

    QAction *action1_4_1 = new QAction(tr("4.1.textures"));
    subMenu1->addAction(action1_4_1);
    connect(action1_4_1, &QAction::triggered, this, [this]{emit courseTriggered("1_4_1");});

    QAction *action1_4_2 = new QAction(tr("4.2.textures_combined"));
    subMenu1->addAction(action1_4_2);
    connect(action1_4_2, &QAction::triggered, this, [this]{emit courseTriggered("1_4_2");});

    QAction *action1_4_3 = new QAction(tr("4.3.textures_exercise2"));
    subMenu1->addAction(action1_4_3);
    connect(action1_4_3, &QAction::triggered, this, [this]{emit courseTriggered("1_4_3");});

    QAction *action1_4_4 = new QAction(tr("4.4.textures_exercise3"));
    subMenu1->addAction(action1_4_4);
    connect(action1_4_4, &QAction::triggered, this, [this]{emit courseTriggered("1_4_4");});

    QAction *action1_4_5 = new QAction(tr("4.5.textures_exercise4"));
    subMenu1->addAction(action1_4_5);
    connect(action1_4_5, &QAction::triggered, this, [this]{emit courseTriggered("1_4_5");});

    QAction *action1_5_1 = new QAction(tr("5.1.transformations"));
    subMenu1->addAction(action1_5_1);
    connect(action1_5_1, &QAction::triggered, this, [this]{emit courseTriggered("1_5_1");});

    QAction *action1_5_2 = new QAction(tr("5.2.transformations_exercise2"));
    subMenu1->addAction(action1_5_2);
    connect(action1_5_2, &QAction::triggered, this, [this]{emit courseTriggered("1_5_2");});

    QAction *action1_6_1 = new QAction(tr("6.1.coordinate_systems"));
    subMenu1->addAction(action1_6_1);
    connect(action1_6_1, &QAction::triggered, this, [this]{emit courseTriggered("1_6_1");});

    QAction *action1_6_2 = new QAction(tr("6.2.coordinate_systems_depth"));
    subMenu1->addAction(action1_6_2);
    connect(action1_6_2, &QAction::triggered, this, [this]{emit courseTriggered("1_6_2");});

    QAction *action1_6_3 = new QAction(tr("6.3.coordinate_systems_multiple"));
    subMenu1->addAction(action1_6_3);
    connect(action1_6_3, &QAction::triggered, this, [this]{emit courseTriggered("1_6_3");});

    QAction *action1_7_1 = new QAction(tr("7.1.camera_circle"));
    subMenu1->addAction(action1_7_1);
    connect(action1_7_1, &QAction::triggered, this, [this]{emit courseTriggered("1_7_1");});

    QAction *action1_7_2 = new QAction(tr("7.2.camera_keyboard_dt"));
    subMenu1->addAction(action1_7_2);
    connect(action1_7_2, &QAction::triggered, this, [this]{emit courseTriggered("1_7_2");});

    QAction *action1_7_3 = new QAction(tr("7.3.camera_mouse_zoom"));
    subMenu1->addAction(action1_7_3);
    connect(action1_7_3, &QAction::triggered, this, [this]{emit courseTriggered("1_7_3");});

    QAction *action1_7_4 = new QAction(tr("7.4.camera_class"));
    subMenu1->addAction(action1_7_4);
    connect(action1_7_4, &QAction::triggered, this, [this]{emit courseTriggered("1_7_4");});

    QMenu *subMenu2 = new QMenu(tr("2.lighting"),this);
    courseMenu->addMenu(subMenu2);

    QAction *action2_1_1 = new QAction(tr("1.1.colors"));
    subMenu2->addAction(action2_1_1);
    connect(action2_1_1, &QAction::triggered, this, [this]{emit courseTriggered("2_1_1");});

    QAction *action2_2_1 = new QAction(tr("2.1.basic_lighting_diffuse"));
    subMenu2->addAction(action2_2_1);
    connect(action2_2_1, &QAction::triggered, this, [this]{emit courseTriggered("2_2_1");});

    QAction *action2_2_2 = new QAction(tr("2.2.basic_lighting_specular"));
    subMenu2->addAction(action2_2_2);
    connect(action2_2_2, &QAction::triggered, this, [this]{emit courseTriggered("2_2_2");});

    QAction *action2_3_1 = new QAction(tr("3.1.materials"));
    subMenu2->addAction(action2_3_1);
    connect(action2_3_1, &QAction::triggered, this, [this]{emit courseTriggered("2_3_1");});

    QAction *action2_3_2 = new QAction(tr("3.2.materials_exercise1"));
    subMenu2->addAction(action2_3_2);
    connect(action2_3_2, &QAction::triggered, this, [this]{emit courseTriggered("2_3_2");});

    QAction *action2_4_1 = new QAction(tr("4.1.lighting_maps_diffuse_map"));
    subMenu2->addAction(action2_4_1);
    connect(action2_4_1, &QAction::triggered, this, [this]{emit courseTriggered("2_4_1");});

    QAction *action2_4_2 = new QAction(tr("4.2.lighting_maps_specular_map"));
    subMenu2->addAction(action2_4_2);
    connect(action2_4_2, &QAction::triggered, this, [this]{emit courseTriggered("2_4_2");});

    QAction *action2_4_4 = new QAction(tr("4.4.lighting_maps_exercise4"));
    subMenu2->addAction(action2_4_4);
    connect(action2_4_4, &QAction::triggered, this, [this]{emit courseTriggered("2_4_4");});

    QAction *action2_5_1= new QAction(tr("5.1.light_casters_directional"));
    subMenu2->addAction(action2_5_1);
    connect(action2_5_1, &QAction::triggered, this, [this]{emit courseTriggered("2_5_1");});

    QAction *action2_5_2= new QAction(tr("5.2.light_casters_point"));
    subMenu2->addAction(action2_5_2);
    connect(action2_5_2, &QAction::triggered, this, [this]{emit courseTriggered("2_5_2");});

    QAction *action2_5_3= new QAction(tr("5.3.light_casters_spot"));
    subMenu2->addAction(action2_5_3);
    connect(action2_5_3, &QAction::triggered, this, [this]{emit courseTriggered("2_5_3");});

    QAction *action2_5_4= new QAction(tr("5.4.light_casters_spot_soft"));
    subMenu2->addAction(action2_5_4);
    connect(action2_5_4, &QAction::triggered, this, [this]{emit courseTriggered("2_5_4");});

    QAction *action2_6_1= new QAction(tr("6.1.multiple_lights"));
    subMenu2->addAction(action2_6_1);
    connect(action2_6_1, &QAction::triggered, this, [this]{emit courseTriggered("2_6_1");});

    QMenu *subMenu3 = new QMenu(tr("3.model_loading"),this);
    courseMenu->addMenu(subMenu3);

    QAction *action3_1_1= new QAction(tr("1.1.model_loading"));
    subMenu3->addAction(action3_1_1);
    connect(action3_1_1, &QAction::triggered, this, [this]{emit courseTriggered("3_1_1");});

    QMenu *subMenu4 = new QMenu(tr("4.advanced_opengl"),this);
    courseMenu->addMenu(subMenu4);

    QAction *action4_1_1= new QAction(tr("1.1.depth_testing"));
    subMenu4->addAction(action4_1_1);
    connect(action4_1_1, &QAction::triggered, this, [this]{emit courseTriggered("4_1_1");});

    QAction *action4_1_2= new QAction(tr("1.2.depth_testing_view"));
    subMenu4->addAction(action4_1_2);
    connect(action4_1_2, &QAction::triggered, this, [this]{emit courseTriggered("4_1_2");});

    QAction *action4_2_1= new QAction(tr("2.1.stencil_testing"));
    subMenu4->addAction(action4_2_1);
    connect(action4_2_1, &QAction::triggered, this, [this]{emit courseTriggered("4_2_1");});

    QAction *action4_3_1= new QAction(tr("3.1.blending_discard"));
    subMenu4->addAction(action4_3_1);
    connect(action4_3_1, &QAction::triggered, this, [this]{emit courseTriggered("4_3_1");});

    QAction *action4_3_2= new QAction(tr("3.2.blending_sort"));
    subMenu4->addAction(action4_3_2);
    connect(action4_3_2, &QAction::triggered, this, [this]{emit courseTriggered("4_3_2");});

    QAction *action4_5_1= new QAction(tr("5.1.framebuffers"));
    subMenu4->addAction(action4_5_1);
    connect(action4_5_1, &QAction::triggered, this, [this]{emit courseTriggered("4_5_1");});

    QAction *action4_5_2= new QAction(tr("5.2.framebuffers_exercise1"));
    subMenu4->addAction(action4_5_2);
    connect(action4_5_2, &QAction::triggered, this, [this]{emit courseTriggered("4_5_2");});

    QAction *action4_6_1= new QAction(tr("6.1.cubemaps_skybox"));
    subMenu4->addAction(action4_6_1);
    connect(action4_6_1, &QAction::triggered, this, [this]{emit courseTriggered("4_6_1");});

    QAction *action4_6_2= new QAction(tr("6.2.cubemaps_environment_mapping"));
    subMenu4->addAction(action4_6_2);
    connect(action4_6_2, &QAction::triggered, this, [this]{emit courseTriggered("4_6_2");});

    QAction *action4_8_1= new QAction(tr("8.1.advanced_glsl_ubo"));
    subMenu4->addAction(action4_8_1);
    connect(action4_8_1, &QAction::triggered, this, [this]{emit courseTriggered("4_8_1");});

    QAction *action4_9_1= new QAction(tr("9.1.geometry_shader_houses"));
    subMenu4->addAction(action4_9_1);
    connect(action4_9_1, &QAction::triggered, this, [this]{emit courseTriggered("4_9_1");});

    QAction *action4_9_2= new QAction(tr("9.2.geometry_shader_exploding"));
    subMenu4->addAction(action4_9_2);
    connect(action4_9_2, &QAction::triggered, this, [this]{emit courseTriggered("4_9_2");});

    QAction *action4_9_3= new QAction(tr("9.3.geometry_shader_normals"));
    subMenu4->addAction(action4_9_3);
    connect(action4_9_3, &QAction::triggered, this, [this]{emit courseTriggered("4_9_3");});

    QAction *action4_10_1= new QAction(tr("10.1.instancing_quads"));
    subMenu4->addAction(action4_10_1);
    connect(action4_10_1, &QAction::triggered, this, [this]{emit courseTriggered("4_10_1");});

    QAction *action4_10_2= new QAction(tr("10.2.asteroids"));
    subMenu4->addAction(action4_10_2);
    connect(action4_10_2, &QAction::triggered, this, [this]{emit courseTriggered("4_10_2");});

    QAction *action4_10_3= new QAction(tr("10.2.asteroids_instanced"));
    subMenu4->addAction(action4_10_3);
    connect(action4_10_3, &QAction::triggered, this, [this]{emit courseTriggered("4_10_3");});

    QAction *action4_11_1= new QAction(tr("11.1.anti_aliasing_msaa"));
    subMenu4->addAction(action4_11_1);
    connect(action4_11_1, &QAction::triggered, this, [this]{emit courseTriggered("4_11_1");});

    QAction *action4_11_2= new QAction(tr("11.2.anti_aliasing_offscreen"));
    subMenu4->addAction(action4_11_2);
    connect(action4_11_2, &QAction::triggered, this, [this]{emit courseTriggered("4_11_2");});

    QMenu *subMenu5 = new QMenu(tr("5.advanced_lighting"),this);
    courseMenu->addMenu(subMenu5);

    QAction *action5_1_1 = new QAction(tr("1.1.advanced_lighting"));
    subMenu5->addAction(action5_1_1);
    connect(action5_1_1, &QAction::triggered, this, [this]{emit courseTriggered("5_1_1");});

    QAction *action5_2_1 = new QAction(tr("2.1.gamma_correction"));
    subMenu5->addAction(action5_2_1);
    connect(action5_2_1, &QAction::triggered, this, [this]{emit courseTriggered("5_2_1");});

    QAction *action5_3_1_1 = new QAction(tr("3.1.1.shadow_mapping_depth"));
    subMenu5->addAction(action5_3_1_1);
    connect(action5_3_1_1, &QAction::triggered, this, [this]{emit courseTriggered("5_3_1_1");});

    QAction *action5_3_1_2 = new QAction(tr("3.1.2.shadow_mapping_base"));
    subMenu5->addAction(action5_3_1_2);
    connect(action5_3_1_2, &QAction::triggered, this, [this]{emit courseTriggered("5_3_1_2");});

    QAction *action5_3_1_3 = new QAction(tr("3.1.3.shadow_mapping"));
    subMenu5->addAction(action5_3_1_3);
    connect(action5_3_1_3, &QAction::triggered, this, [this]{emit courseTriggered("5_3_1_3");});

    QAction *action5_3_2_1 = new QAction(tr("3.2.1.point_shadows"));
    subMenu5->addAction(action5_3_2_1);
    connect(action5_3_2_1, &QAction::triggered, this, [this]{emit courseTriggered("5_3_2_1");});

    QAction *action5_3_2_2 = new QAction(tr("3.2.2.point_shadows_soft"));
    subMenu5->addAction(action5_3_2_2);
    connect(action5_3_2_2, &QAction::triggered, this, [this]{emit courseTriggered("5_3_2_2");});

    QAction *action5_4_1 = new QAction(tr("4.1.normal_mapping"));
    subMenu5->addAction(action5_4_1);
    connect(action5_4_1, &QAction::triggered, this, [this]{emit courseTriggered("5_4_1");});

    QAction *action5_5_1 = new QAction(tr("5.1.parallax_mapping"));
    subMenu5->addAction(action5_5_1);
    connect(action5_5_1, &QAction::triggered, this, [this]{emit courseTriggered("5_5_1");});

    QAction *action5_5_2 = new QAction(tr("5.2.steep_parallax_mapping"));
    subMenu5->addAction(action5_5_2);
    connect(action5_5_2, &QAction::triggered, this, [this]{emit courseTriggered("5_5_2");});

    QAction *action5_5_3 = new QAction(tr("5.3.parallax_occlusion_mapping"));
    subMenu5->addAction(action5_5_3);
    connect(action5_5_3, &QAction::triggered, this, [this]{emit courseTriggered("5_5_3");});

    QAction *action5_6_1 = new QAction(tr("6.1.hdr"));
    subMenu5->addAction(action5_6_1);
    connect(action5_6_1, &QAction::triggered, this, [this]{emit courseTriggered("5_6_1");});

    QAction *action5_7_1 = new QAction(tr("7.1.bloom"));
    subMenu5->addAction(action5_7_1);
    connect(action5_7_1, &QAction::triggered, this, [this]{emit courseTriggered("5_7_1");});

    QAction *action5_8_1 = new QAction(tr("8.1.deferred_shading"));
    subMenu5->addAction(action5_8_1);
    connect(action5_8_1, &QAction::triggered, this, [this]{emit courseTriggered("5_8_1");});

    QAction *action5_8_2 = new QAction(tr("8.2.deferred_shading_volumes"));
    subMenu5->addAction(action5_8_2);
    connect(action5_8_2, &QAction::triggered, this, [this]{emit courseTriggered("5_8_2");});

    QAction *action5_9_1 = new QAction(tr("9.1.ssao"));
    subMenu5->addAction(action5_9_1);
    connect(action5_9_1, &QAction::triggered, this, [this]{emit courseTriggered("5_9_1");});

    QMenu *subMenu6 = new QMenu(tr("6.pbr"),this);
    courseMenu->addMenu(subMenu6);

    QAction *action6_1_1 = new QAction(tr("1.1.lighting"));
    subMenu6->addAction(action6_1_1);
    connect(action6_1_1, &QAction::triggered, this, [this]{emit courseTriggered("6_1_1");});

    QAction *action6_1_2 = new QAction(tr("1.2.lighting_textured"));
    subMenu6->addAction(action6_1_2);
    connect(action6_1_2, &QAction::triggered, this, [this]{emit courseTriggered("6_1_2");});

    QAction *action6_2_1 = new QAction(tr("2.1.1.ibl_irrandiance_conversion"));
    subMenu6->addAction(action6_2_1);
    connect(action6_2_1, &QAction::triggered, this, [this]{emit courseTriggered("6_2_1_1");});

    QAction *action6_2_1_2 = new QAction(tr("2.1.2.ibl_irrandiance"));
    subMenu6->addAction(action6_2_1_2);
    connect(action6_2_1_2, &QAction::triggered, this, [this]{emit courseTriggered("6_2_1_2");});

    QAction *action6_2_2_1 = new QAction(tr("2.2.1.ibl_specular"));
    subMenu6->addAction(action6_2_2_1);
    connect(action6_2_2_1, &QAction::triggered, this, [this]{emit courseTriggered("6_2_2_1");});

    QAction *action6_2_2_2 = new QAction(tr("2.2.2.ibl_specular_textured"));
    subMenu6->addAction(action6_2_2_2);
    connect(action6_2_2_2, &QAction::triggered, this, [this]{emit courseTriggered("6_2_2_2");});

    QMenu *subMenu7 = new QMenu(tr("7.in_practice"),this);
    courseMenu->addMenu(subMenu7);

    QAction *action7_1_1 = new QAction(tr("1.1.debugging"));
    subMenu7->addAction(action7_1_1);
    connect(action7_1_1, &QAction::triggered, this, [this]{emit courseTriggered("7_1_1");});

    QHBoxLayout *hLayout = new QHBoxLayout(ui->centralwidget);
    hLayout->setSpacing(0);
    hLayout->setMargin(0);
    ui->centralwidget->setLayout(hLayout);

    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setOption(QSurfaceFormat::DebugContext);
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    format.setVersion(3,3);

    hLayout->addWidget(spliter);
    treeWidget = new MyDockWidget(spliter);
    treeWidget->setWindowTitle(tr("Scene"));
    treeWidget->setAllowedAreas(Qt::LeftDockWidgetArea);
    treeWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    treeWidget->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);

    glWindow = new GlWindow(this, spliter);
    glWindow->setFormat(format);

    inspectorWidget = new InspectorDockWidget(spliter);
    inspectorWidget->setAllowedAreas(Qt::RightDockWidgetArea);

    example1 = new ProxyExample1(this);
    example2 = new ProxyExample2(this);   
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setInspectorProxy(InspectorProxy *proxy)
{
    inspectorWidget->getInspector()->setProxy(proxy);
}

void MainWindow::setInspectorProperty(const QString &propertyId, const QVariant &value)
{
    inspectorWidget->getInspector()->updateProperty(propertyId, value);
}

void MainWindow::actionTriggered_inspect_example2()
{
    //setInspectorProxy(example1);
    setInspectorProxy(example2);
}

void MainWindow::actionTriggered_uninspect_example2()
{
    setInspectorProxy(nullptr);
}

void MainWindow::actionTriggered_showMatrix()
{
    MatrixEditor *editor = new MatrixEditor();
    editor->setValue(QMatrix4x4());
    editor->show();
}
