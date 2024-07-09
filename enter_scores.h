#ifndef ENTER_SCORES_H
#define ENTER_SCORES_H

#include <QWidget>

namespace Ui {
class enter_scores;
}

class enter_scores : public QWidget
{
    Q_OBJECT

public:
    explicit enter_scores(int studentId, int courseId, int id, QWidget *parent = nullptr);
    ~enter_scores();

private slots:
    void on_comfirm_clicked();

    void on_cancel_clicked();

private:
    Ui::enter_scores *ui;
    int studentId;
    int courseId;
    int id;

};

#endif // ENTER_SCORES_H
