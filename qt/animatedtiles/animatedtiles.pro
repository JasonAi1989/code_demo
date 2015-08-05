SOURCES = main.cpp
RESOURCES = animatedtiles.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/animation/animatedtiles
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS animatedtiles.pro images
sources.path = $$[QT_INSTALL_EXAMPLES]/animation/animatedtiles
INSTALLS += target sources

symbian {
    TARGET.UID3 = 0xA000D7D1
    include($$PWD/../../symbianpkgrules.pri)
}
maemo5: include($$PWD/../../maemo5pkgrules.pri)
contains(MEEGO_EDITION,harmattan): include($$PWD/../../harmattanpkgrules.pri)
