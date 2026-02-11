# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = lab_03

CONFIG += c++20

QT = core gui widgets

HEADERS = \
	mainwindow.h \
	object/abstractobject.h \
	modelvisitor/modelvisitor.h \
	modelvisitor/movevisitor.h \
	modelvisitor/rotatevisitor.h \
	modelvisitor/scalevisitor.h \
	object/carcas/carcas.h \
	object/model.h \
	object/carcas/AbstractCarcas.h \
	builder/carcasbuilder.h \
	builder/BaseCarcasBuilder.h \
	loader/loader.h \
	loader/abstractreader.h \
	loader/filereader.h \
	manager/base_manager.h \
	manager/transform_manager.h \
	manager/load_manager.h \
	object/camera/camera.h \
	scene/scene.h \
	builder/basedirector.h \
	builder/carcasdirector.h \
	builder/directorcreator.h \
	draw/abstractgraphicfactory.h \
	draw/abstractdrawer.h \
	draw/qtdrawer.h \
	draw/qtfactory.h \
	draw/drawvisitor.h \
	draw/drawall.h \
	manager/scene_manager.h \
	manager/draw_manager.h \
	facade/facade.h \
	command/basecommand.h \
	command/modelcommand.h \
	command/cameracommand.h \
	command/scenecommand.h \
	command/drawcommand.h \
	Exception.h \
	visitor/abstractvisitor.h \
	draw/drawcomplex.h \
	object/carcas/matrixcarcas.h \
	builder/matrixbuilder.h \
	loader/binaryreader.h \
        solution/base_solution.h \
        solution/load_solution.h

SOURCES = \
	main.cpp \
	mainwindow.cpp \
	object/abstractobject.cpp \
	modelvisitor/movevisitor.cpp \
	modelvisitor/rotatevisitor.cpp \
	modelvisitor/scalevisitor.cpp \
	object/carcas/carcas.cpp \
	object/model.cpp \
	builder/carcasbuilder.cpp \
	loader/loader.cpp \
	loader/abstractreader.cpp \
	loader/filereader.cpp \
	manager/base_manager.cpp \
	manager/transform_manager.cpp \
	manager/load_manager.cpp \
	object/camera/camera.cpp \
	scene/scene.cpp \
	builder/basedirector.cpp \
	builder/carcasdirector.cpp \
	builder/directorcreator.cpp \
	draw/abstractgraphicfactory.cpp \
	draw/abstractdrawer.cpp \
	draw/qtdrawer.cpp \
	draw/qtfactory.cpp \
	draw/drawvisitor.cpp \
	draw/drawall.cpp \
	manager/scene_manager.cpp \
	manager/draw_manager.cpp \
	facade/facade.cpp \
	command/basecommand.cpp \
	command/modelcommand.cpp \
	command/cameracommand.cpp \
	command/scenecommand.cpp \
	command/drawcommand.cpp \
	visitor/abstractvisitor.cpp \
	draw/drawcomplex.cpp \
	object/carcas/matrixcarcas.cpp \
	builder/matrixbuilder.cpp \
        loader/binaryreader.cpp \
        solution/base_solution.cpp \
        solution/load_solution.cpp

FORMS += \
    mainwindow.ui

DISTFILES += \
    data/cone.txt \
    data/cube.txt \
    data/tesseract.txt
#DEFINES = 

