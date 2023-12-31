QT += widgets
requires(qtConfig(treeview))

FORMS       = mainwindow.ui
HEADERS     = mainwindow.h \
              qmytableviewbtndelegate.h \
              qmytableviewcheckboxdelegate.h \
              treeitem.h \
              treemodel.h
RESOURCES   = editabletreemodel.qrc
SOURCES     = mainwindow.cpp \
              qmytableviewbtndelegate.cpp \
              qmytableviewcheckboxdelegate.cpp \
              treeitem.cpp \
              treemodel.cpp \
              main.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/itemviews/editabletreemodel
INSTALLS += target
