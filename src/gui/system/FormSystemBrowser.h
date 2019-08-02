#ifndef FORMSYSTEMBROWSER_H
#define FORMSYSTEMBROWSER_H

#include <QWidget>
#include <QFileSystemModel>
#include <QItemSelection>
#include <QStringListModel>

namespace Ui {
class FormSystemBrowser;
}

class FormSystemBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit FormSystemBrowser(QWidget *parent = nullptr);
    ~FormSystemBrowser();

    void openFile();

protected:
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void canceled();
    void openned(QString filename);

public slots:
    void on_changeSystemSelected(const QItemSelection&, const QItemSelection &);
    void on_changeCurrentSelected(const QItemSelection&, const QItemSelection &);
    void on_changeRecentSelected(const QItemSelection&, const QItemSelection &);

private slots:
    void on_pushButton_openFile_clicked();

    void on_pushButton_cancel_clicked();

private:
    void updateRecent();

private:
    Ui::FormSystemBrowser *ui;

    QFileSystemModel * m_model;
    QStringListModel * m_recent;
};

#endif // FORMSYSTEMBROWSER_H
