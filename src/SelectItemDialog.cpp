#include "SelectItemDialog.h"
#include "ui_SelectItemDialog.h"

SelectItemDialog::SelectItemDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SelectItemDialog)
{
	ui->setupUi(this);
	Qt::WindowFlags flags = windowFlags();
	flags &= ~Qt::WindowContextHelpButtonHint;
	setWindowFlags(flags);
}

SelectItemDialog::~SelectItemDialog()
{
	delete ui;
}

void SelectItemDialog::addItem(const QString &id, const QString &text)
{
	auto *item = new QListWidgetItem;
	item->setText(text);
	item->setData(Qt::UserRole, id);
	ui->listWidget->addItem(item);
}

void SelectItemDialog::select(QString const &id)
{
	int n = ui->listWidget->count();
	for (int i = 0; i < n; i++) {
		QListWidgetItem *p = ui->listWidget->item(i);
		if (p->data(Qt::UserRole).toString() == id) {
			ui->listWidget->setCurrentRow(i);
			return;
		}
	}
}

SelectItemDialog::Item SelectItemDialog::item() const
{
	Item ret;
	QListWidgetItem *p = ui->listWidget->currentItem();
	if (p) {
		ret.id = p->data(Qt::UserRole).toString();
		ret.text = p->text();
	}
	return ret;
}

void SelectItemDialog::on_listWidget_itemDoubleClicked(QListWidgetItem *)
{
	done(Accepted);
}
