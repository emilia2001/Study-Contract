#include "Service.h"
#include "Gui.h"
#include "Tests.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);
    /*
    //run_all_tests();
    RepositoryFile repo{ "discipline.txt" };
    Validator valid;
    Contract contract{ repo };
    Service serv{ repo, valid , contract };
    GUI gui{ serv, contract };
    gui.show();*/

    
        QWidget* main = new QWidget();
        QFormLayout* fL = new QFormLayout(main);
        QLabel* lbl = new QLabel("Name:", main);
        QLineEdit* txt = new QLineEdit(main);
        fL->addRow(lbl, txt);
        main->show();
        main->setWindowTitle("Layout");
        //fix the height to the "ideal" height
        main->setFixedHeight(main->sizeHint().height());
    


    return a.exec();
}
