#ifndef FORMSYSTEMBROWSER_H
#define FORMSYSTEMBROWSER_H

#include <QFileSystemModel>
#include <QItemSelection>
#include <QSettings>
#include <QStringListModel>
#include <QWidget>

namespace Ui {
class FormSystemBrowser;
}

enum Mode {
    OPEN,
    SAVE,
    IMPORT
};

class FormSystemBrowser : public QWidget {
    Q_OBJECT

public:
    explicit FormSystemBrowser(QWidget* parent = nullptr);
    ~FormSystemBrowser();

    void openFile();
    void saveFile();
    void importFile();
    void actionFile();
    //    void setGoliathFilter();
    //    void setAssimpFilter();
    void setMode(Mode mode);

    void registerOpennedDir(QString path);

protected:
    void keyPressEvent(QKeyEvent* event) override;

signals:
    void canceled();
    void openned(QString filename);
    void saved(QString file);
    void imported(QString file);


public slots:
    void on_changeSystemSelected(const QItemSelection&, const QItemSelection&);
    void on_changeCurrentSelected(const QItemSelection&, const QItemSelection&);
    void on_changeRecentSelected(const QItemSelection&, const QItemSelection&);

private slots:
    void on_pushButton_actionFile_clicked();
    void on_pushButton_cancel_clicked();
    void on_pushButton_parent_clicked();
    void on_lineEdit_currentFile_textChanged(const QString& arg1);

private:
//    void pullSettingsRecentModel();

    void updateRecent(const QModelIndex& index);
    void updateCurrent(const QModelIndex& index);

private:
    Ui::FormSystemBrowser* ui;

    QFileSystemModel* m_model;
    QStringListModel* m_recent;
//    QStringListModel* m_previous;

    QSettings m_settings;
    QString m_rootPath;

    Mode m_mode;
};

#endif // FORMSYSTEMBROWSER_H
