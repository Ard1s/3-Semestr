#include "mainwindow.h"

int main(int argc, char *argv[]) 
{
	Q_INIT_RESOURCE(images); 
	QApplication app(argc, argv); 
	app.setQuitOnLastWindowClosed(false);  

	MainWindow::theIcon = QIcon(":/hourglass.ico");

	QStringList arguments = app.arguments();

	
	MainWindow *w = new MainWindow();
	if ( arguments.size() > 1 ) 
{
		w->setWindowTitle(arguments.mid(1).join(' '));
	}
	w->show();

	return app.exec();
}
