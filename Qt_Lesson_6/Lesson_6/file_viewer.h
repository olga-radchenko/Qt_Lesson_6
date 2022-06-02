#ifndef FILE_VIEWER_H
#define FILE_VIEWER_H

#include <QWidget>
#include <QFileSystemModel>

namespace Ui {
class FileViewer;
}

class FileViewer : public QWidget
{
    Q_OBJECT

    QFileSystemModel* fsModel;

    void showFolder();

public:
    explicit FileViewer(QWidget *parent = nullptr);
    ~FileViewer();

    void switchLanguage();

private:
    Ui::FileViewer *ui;

private slots:
    void onTreeViewClicked(const QModelIndex &index);
    void onTreeViewDoubleClicked(const QModelIndex &index);
    void on_openBtn_clicked();
    void on_dirLineEdit_editingFinished();
    void on_upBtn_clicked();
    void on_backBtn_clicked();
};

#endif // FILE_VIEWER_H
