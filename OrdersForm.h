#pragma once
#include "TransportCompany.h"
#include "Client.h"
#include "Tariff.h"
#include "Order.h"
#include "sqlite3.h"
#include <string>


namespace Laba34 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;


	/// <summary>
	/// Сводка для OrdersForm
	/// </summary>
	public ref class OrdersForm : public System::Windows::Forms::Form
	{

	private:
		TransportCompany^ company;
	private: System::Windows::Forms::Button^ exportOrders;
	private: System::Windows::Forms::Button^ importOrders;
		   BindingSource^ ordersBinding;
	private: System::Windows::Forms::Button^ exportOrdersCSV;
	private: System::Windows::Forms::Button^ importOrderCSV;

	private:
		System::Data::DataTable^ ordersTable;

	public:
		OrdersForm(TransportCompany^ c)
		{
			InitializeComponent();
			company = c;

			ordersGrid->AutoGenerateColumns = false;

			DataGridViewTextBoxColumn^ colClient = gcnew DataGridViewTextBoxColumn();
			colClient->Name = "ClientName";
			colClient->HeaderText = "Клиент";
			colClient->DataPropertyName = "ClientName";
			colClient->SortMode = DataGridViewColumnSortMode::Automatic;
			ordersGrid->Columns->Add(colClient);

			DataGridViewTextBoxColumn^ colPhone = gcnew DataGridViewTextBoxColumn();
			colPhone->Name = "ClientPhone";
			colPhone->HeaderText = "Телефон";
			colPhone->DataPropertyName = "ClientPhone";
			colPhone->SortMode = DataGridViewColumnSortMode::Automatic;
			ordersGrid->Columns->Add(colPhone);

			DataGridViewTextBoxColumn^ colTariff = gcnew DataGridViewTextBoxColumn();
			colTariff->Name = "TariffType";
			colTariff->HeaderText = "Тариф";
			colTariff->DataPropertyName = "TariffType";
			colTariff->SortMode = DataGridViewColumnSortMode::Automatic;
			ordersGrid->Columns->Add(colTariff);

			DataGridViewTextBoxColumn^ colVolume = gcnew DataGridViewTextBoxColumn();
			colVolume->Name = "Volume";
			colVolume->HeaderText = "Месяцы";
			colVolume->DataPropertyName = "Volume";
			colVolume->SortMode = DataGridViewColumnSortMode::Automatic;
			ordersGrid->Columns->Add(colVolume);

			DataGridViewTextBoxColumn^ colTotal = gcnew DataGridViewTextBoxColumn();
			colTotal->Name = "TotalCost";
			colTotal->HeaderText = "Сумма";
			colTotal->DataPropertyName = "TotalCost";
			colTotal->SortMode = DataGridViewColumnSortMode::Automatic;
			ordersGrid->Columns->Add(colTotal);

			// Заполняем ComboBox клиентами
			comboClients->DataSource = company->GetClients();
			comboClients->DisplayMember = "Name";

			// Заполняем ComboBox тарифами
			comboTariffs->DataSource = company->GetTariffs();
			comboTariffs->DisplayMember = "TypeString";

			// Привязываем DataGridView к заказам
			ordersTable = gcnew System::Data::DataTable();



			// Колонки
			ordersTable->Columns->Add("ClientName", String::typeid);
			ordersTable->Columns->Add("ClientPhone", String::typeid);
			ordersTable->Columns->Add("TariffType", String::typeid);
			ordersTable->Columns->Add("Volume", Double::typeid);
			ordersTable->Columns->Add("TotalCost", Double::typeid);
			// Колонка для хранения самого объекта Order
			ordersTable->Columns->Add("OrderObject", Order::typeid);


			for each (Order ^ order in company->GetOrders()) {
				ordersTable->Rows->Add(
					order->ClientName,
					order->ClientPhone,
					order->TariffType,
					order->Volume,
					order->TotalCost,
					order   // <-- ОБЯЗАТЕЛЬНО!
				);
			}



			// Привязываем DataGridView к DataTable
			ordersGrid->DataSource = ordersTable;

		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~OrdersForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^ ordersGrid;
	protected:
	private: System::Windows::Forms::ComboBox^ comboClients;
	private: System::Windows::Forms::Label^ lblClient;
	private: System::Windows::Forms::ComboBox^ comboTariffs;
	private: System::Windows::Forms::Label^ lblTariff;
	private: System::Windows::Forms::TextBox^ txtVolume;
	private: System::Windows::Forms::Label^ lblVolume;
	private: System::Windows::Forms::Button^ btnAddOrder;
	private: System::Windows::Forms::Button^ btnDeleteOrder;



	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->ordersGrid = (gcnew System::Windows::Forms::DataGridView());
			this->comboClients = (gcnew System::Windows::Forms::ComboBox());
			this->lblClient = (gcnew System::Windows::Forms::Label());
			this->comboTariffs = (gcnew System::Windows::Forms::ComboBox());
			this->lblTariff = (gcnew System::Windows::Forms::Label());
			this->txtVolume = (gcnew System::Windows::Forms::TextBox());
			this->lblVolume = (gcnew System::Windows::Forms::Label());
			this->btnAddOrder = (gcnew System::Windows::Forms::Button());
			this->btnDeleteOrder = (gcnew System::Windows::Forms::Button());
			this->exportOrders = (gcnew System::Windows::Forms::Button());
			this->importOrders = (gcnew System::Windows::Forms::Button());
			this->exportOrdersCSV = (gcnew System::Windows::Forms::Button());
			this->importOrderCSV = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ordersGrid))->BeginInit();
			this->SuspendLayout();
			// 
			// ordersGrid
			// 
			this->ordersGrid->AllowUserToAddRows = false;
			this->ordersGrid->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->ordersGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->ordersGrid->Location = System::Drawing::Point(12, 12);
			this->ordersGrid->Name = L"ordersGrid";
			this->ordersGrid->ReadOnly = true;
			this->ordersGrid->RowHeadersWidth = 51;
			this->ordersGrid->Size = System::Drawing::Size(550, 200);
			this->ordersGrid->TabIndex = 0;
			this->ordersGrid->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &OrdersForm::ordersGrid_CellClick);
			// 
			// comboClients
			// 
			this->comboClients->FormattingEnabled = true;
			this->comboClients->Location = System::Drawing::Point(62, 218);
			this->comboClients->Name = L"comboClients";
			this->comboClients->Size = System::Drawing::Size(121, 21);
			this->comboClients->TabIndex = 1;
			// 
			// lblClient
			// 
			this->lblClient->AutoSize = true;
			this->lblClient->Location = System::Drawing::Point(13, 218);
			this->lblClient->Name = L"lblClient";
			this->lblClient->Size = System::Drawing::Size(46, 13);
			this->lblClient->TabIndex = 2;
			this->lblClient->Text = L"Клиент:";
			this->lblClient->Click += gcnew System::EventHandler(this, &OrdersForm::lblClient_Click);
			// 
			// comboTariffs
			// 
			this->comboTariffs->FormattingEnabled = true;
			this->comboTariffs->Location = System::Drawing::Point(62, 256);
			this->comboTariffs->Name = L"comboTariffs";
			this->comboTariffs->Size = System::Drawing::Size(121, 21);
			this->comboTariffs->TabIndex = 3;
			// 
			// lblTariff
			// 
			this->lblTariff->AutoSize = true;
			this->lblTariff->Location = System::Drawing::Point(16, 256);
			this->lblTariff->Name = L"lblTariff";
			this->lblTariff->Size = System::Drawing::Size(43, 13);
			this->lblTariff->TabIndex = 4;
			this->lblTariff->Text = L"Тариф:";
			// 
			// txtVolume
			// 
			this->txtVolume->Location = System::Drawing::Point(62, 295);
			this->txtVolume->Name = L"txtVolume";
			this->txtVolume->Size = System::Drawing::Size(100, 20);
			this->txtVolume->TabIndex = 5;
			// 
			// lblVolume
			// 
			this->lblVolume->AutoSize = true;
			this->lblVolume->Location = System::Drawing::Point(16, 295);
			this->lblVolume->Name = L"lblVolume";
			this->lblVolume->Size = System::Drawing::Size(51, 13);
			this->lblVolume->TabIndex = 6;
			this->lblVolume->Text = L"Месяцы:";
			// 
			// btnAddOrder
			// 
			this->btnAddOrder->Location = System::Drawing::Point(300, 218);
			this->btnAddOrder->Name = L"btnAddOrder";
			this->btnAddOrder->Size = System::Drawing::Size(75, 23);
			this->btnAddOrder->TabIndex = 7;
			this->btnAddOrder->Text = L"Добавить заказ";
			this->btnAddOrder->UseVisualStyleBackColor = true;
			this->btnAddOrder->Click += gcnew System::EventHandler(this, &OrdersForm::btnAddOrder_Click);
			// 
			// btnDeleteOrder
			// 
			this->btnDeleteOrder->Location = System::Drawing::Point(464, 218);
			this->btnDeleteOrder->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->btnDeleteOrder->Name = L"btnDeleteOrder";
			this->btnDeleteOrder->Size = System::Drawing::Size(75, 23);
			this->btnDeleteOrder->TabIndex = 8;
			this->btnDeleteOrder->Text = L"Удалить заказ";
			this->btnDeleteOrder->UseVisualStyleBackColor = true;
			this->btnDeleteOrder->Click += gcnew System::EventHandler(this, &OrdersForm::btnDeleteOrder_Click);
			// 
			// exportOrders
			// 
			this->exportOrders->Location = System::Drawing::Point(300, 247);
			this->exportOrders->Name = L"exportOrders";
			this->exportOrders->Size = System::Drawing::Size(136, 23);
			this->exportOrders->TabIndex = 9;
			this->exportOrders->Text = L"Выгрузить тарифы SQL";
			this->exportOrders->UseVisualStyleBackColor = true;
			this->exportOrders->Click += gcnew System::EventHandler(this, &OrdersForm::exportOrders_Click);
			// 
			// importOrders
			// 
			this->importOrders->Location = System::Drawing::Point(447, 246);
			this->importOrders->Name = L"importOrders";
			this->importOrders->Size = System::Drawing::Size(136, 23);
			this->importOrders->TabIndex = 10;
			this->importOrders->Text = L"Загрузить тарифы SQL";
			this->importOrders->UseVisualStyleBackColor = true;
			this->importOrders->Click += gcnew System::EventHandler(this, &OrdersForm::importOrders_Click);
			// 
			// exportOrdersCSV
			// 
			this->exportOrdersCSV->Location = System::Drawing::Point(299, 285);
			this->exportOrdersCSV->Name = L"exportOrdersCSV";
			this->exportOrdersCSV->Size = System::Drawing::Size(137, 23);
			this->exportOrdersCSV->TabIndex = 12;
			this->exportOrdersCSV->Text = L"Выгрузить тарифы CSV";
			this->exportOrdersCSV->UseVisualStyleBackColor = true;
			this->exportOrdersCSV->Click += gcnew System::EventHandler(this, &OrdersForm::exportOrdersCSV_Click);
			// 
			// importOrderCSV
			// 
			this->importOrderCSV->Location = System::Drawing::Point(447, 285);
			this->importOrderCSV->Name = L"importOrderCSV";
			this->importOrderCSV->Size = System::Drawing::Size(137, 23);
			this->importOrderCSV->TabIndex = 13;
			this->importOrderCSV->Text = L"Загрузить тарифы CSV";
			this->importOrderCSV->UseVisualStyleBackColor = true;
			this->importOrderCSV->Click += gcnew System::EventHandler(this, &OrdersForm::importOrderCSV_Click);
			// 
			// OrdersForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(595, 350);
			this->Controls->Add(this->importOrderCSV);
			this->Controls->Add(this->exportOrdersCSV);
			this->Controls->Add(this->importOrders);
			this->Controls->Add(this->exportOrders);
			this->Controls->Add(this->btnDeleteOrder);
			this->Controls->Add(this->btnAddOrder);
			this->Controls->Add(this->lblVolume);
			this->Controls->Add(this->txtVolume);
			this->Controls->Add(this->lblTariff);
			this->Controls->Add(this->comboTariffs);
			this->Controls->Add(this->lblClient);
			this->Controls->Add(this->comboClients);
			this->Controls->Add(this->ordersGrid);
			this->Name = L"OrdersForm";
			this->Text = L"OrdersForm";
			this->Load += gcnew System::EventHandler(this, &OrdersForm::OrdersForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ordersGrid))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void lblClient_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void btnAddOrder_Click(System::Object^ sender, System::EventArgs^ e) {
		// Проверка, выбран ли клиент
		if (comboClients->SelectedItem == nullptr) {
			MessageBox::Show("Пожалуйста, выберите клиента.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		// Проверка, выбран ли тариф
		if (comboTariffs->SelectedItem == nullptr) {
			MessageBox::Show("Пожалуйста, выберите тариф.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		// Проверка ввода объёма
		if (String::IsNullOrWhiteSpace(txtVolume->Text)) {
			MessageBox::Show("Пожалуйста, введите объём заказа.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		// Попытка конвертации в число
		double volume;
		if (!Double::TryParse(txtVolume->Text, volume)) {
			MessageBox::Show("Объём заказа должен быть числом.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		if (volume <= 0) {
			MessageBox::Show("Объём заказа должен быть положительным числом.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		// Создание заказа
		Client^ client = (Client^)comboClients->SelectedItem;
		Tariff^ tariff = (Tariff^)comboTariffs->SelectedItem;
		company->CreateOrder(client, tariff, volume);

		// Обновление таблицы без обращения к CurrentRow
		ordersTable->Rows->Clear();
		for each (Order ^ order in company->GetOrders()) {
			ordersTable->Rows->Add(
				order->ClientName,
				order->ClientPhone,
				order->TariffType,
				order->Volume,
				order->TotalCost,
				order
			);
		}
	}
	public: void RefreshOrdersTable() {
		// Очищаем старые строки
		//ordersTable->Rows->Clear();

		// Добавляем все текущие заказы из компании
		for each (Order ^ order in company->GetOrders()) {
			ordersTable->Rows->Add(
				order->ClientName,
				order->ClientPhone,
				order->TariffType,
				order->Volume,
				order->TotalCost,
				order   // Храним сам объект заказа
			);
		}
	}

	private: System::Void btnDeleteOrder_Click(System::Object^ sender, System::EventArgs^ e) {
		if (ordersGrid->CurrentRow == nullptr || ordersGrid->CurrentRow->Index < 0) {
			MessageBox::Show("Пожалуйста, выберите заказ.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		System::Data::DataRowView^ rowView = dynamic_cast<System::Data::DataRowView^>(ordersGrid->CurrentRow->DataBoundItem);
		if (rowView == nullptr) {
			MessageBox::Show("Не удалось получить данные выбранного заказа.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		Order^ order = (Order^)rowView["OrderObject"];
		company->RemoveOrder(order);

		// Обновляем таблицу
		ordersTable->Rows->Clear();
		for each (Order ^ order in company->GetOrders()) {
			ordersTable->Rows->Add(
				order->ClientName,
				order->ClientPhone,
				order->TariffType,
				order->Volume,
				order->TotalCost,
				order
			);
		}
	}

	private: System::Void ordersGrid_CellClick(System::Object^ sender,
		System::Windows::Forms::DataGridViewCellEventArgs^ e)
	{
		if (e->RowIndex < 0) return; // Нажали на заголовок — игнор
	}

	private:
		Client^ GetOrCreateClient(String^ name, String^ phone)
		{
			for each (Client ^ c in company->GetClients())
				if (c->Name == name)
					return c;

			// Если клиента нет — создаём
			Client^ newClient = gcnew Client(name, phone);
			company->AddClient(newClient);
			return newClient;
		}

		Tariff^ GetOrCreateTariff(String^ typeStr, double price)
		{
			for each (Tariff ^ t in company->GetTariffs())
				if (t->TypeString == typeStr)
					return t;

			// Если тарифа нет — создаём
			CargoType type;
			if (typeStr == "Интернет") type = CargoType::General;
			else if (typeStr == "Вода") type = CargoType::Fragile;
			else if (typeStr == "Ремонт") type = CargoType::Hazardous;
			else type = CargoType::Refrigerated;

			Tariff^ newTariff = gcnew Tariff(type, price);
			company->AddTariff(newTariff);
			return newTariff;
		}

	private: System::Void exportOrders_Click(System::Object^ sender, System::EventArgs^ e) {
		SaveFileDialog^ saveDialog = gcnew SaveFileDialog();
		saveDialog->Filter = "SQLite Database (*.db)|*.db";
		saveDialog->FileName = "Orders.db";

		if (saveDialog->ShowDialog() != System::Windows::Forms::DialogResult::OK)
			return;

		sqlite3* db;
		int rc = sqlite3_open(StringToUTF8(saveDialog->FileName).c_str(), &db);

		if (rc != SQLITE_OK) {
			MessageBox::Show("Не удалось создать базу данных: " + gcnew String(sqlite3_errmsg(db)),
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			sqlite3_close(db);
			return;
		}

		// Создаём таблицу (если не существует)
		const char* createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS Orders (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            client_name TEXT NOT NULL,
            client_phone TEXT NOT NULL,
            tariff_type TEXT NOT NULL,
            volume REAL NOT NULL,
            total_cost REAL NOT NULL
        );
    )";

		rc = sqlite3_exec(db, createTableSQL, nullptr, nullptr, nullptr);
		if (rc != SQLITE_OK) {
			MessageBox::Show("Ошибка создания таблицы: " + gcnew String(sqlite3_errmsg(db)),
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			sqlite3_close(db);
			return;
		}

		// Очищаем старые данные (опционально)
		sqlite3_exec(db, "DELETE FROM Orders;", nullptr, nullptr, nullptr);

		// Подготавливаем SQL-запрос
		const char* insertSQL = "INSERT INTO Orders (client_name, client_phone, tariff_type, volume, total_cost) VALUES (?, ?, ?, ?, ?);";
		sqlite3_stmt* stmt;
		rc = sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr);

		if (rc != SQLITE_OK) {
			MessageBox::Show("Ошибка подготовки запроса: " + gcnew String(sqlite3_errmsg(db)),
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			sqlite3_close(db);
			return;
		}

		// Вставляем заказы
		try {
			for each (Order ^ order in company->GetOrders()) {
				sqlite3_bind_text(stmt, 1, StringToUTF8(order->ClientName).c_str(), -1, SQLITE_TRANSIENT);
				sqlite3_bind_text(stmt, 2, StringToUTF8(order->ClientPhone).c_str(), -1, SQLITE_TRANSIENT);
				sqlite3_bind_text(stmt, 3, StringToUTF8(order->TariffType).c_str(), -1, SQLITE_TRANSIENT);
				sqlite3_bind_double(stmt, 4, order->Volume);
				sqlite3_bind_double(stmt, 5, order->TotalCost);

				rc = sqlite3_step(stmt);
				if (rc != SQLITE_DONE) {
					throw gcnew Exception("Ошибка при добавлении заказа: " + gcnew String(sqlite3_errmsg(db)));
				}

				sqlite3_reset(stmt);
			}

			MessageBox::Show("Заказы успешно сохранены в базу данных:\n" + saveDialog->FileName,
				"Экспорт завершён", MessageBoxButtons::OK, MessageBoxIcon::Information);

		}
		catch (Exception^ ex) {
			MessageBox::Show("Ошибка при экспорте: " + ex->Message,
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}

		sqlite3_finalize(stmt);
		sqlite3_close(db);
	}
	private: System::Void importOrders_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ openDialog = gcnew OpenFileDialog();
		openDialog->Filter = "SQLite Database (*.db)|*.db";

		if (openDialog->ShowDialog() != System::Windows::Forms::DialogResult::OK)
			return;

		sqlite3* db;
		int rc = sqlite3_open(StringToUTF8(openDialog->FileName).c_str(), &db);

		if (rc != SQLITE_OK) {
			MessageBox::Show("Не удалось открыть базу данных: " + gcnew String(sqlite3_errmsg(db)),
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		const char* selectSQL = "SELECT client_name, client_phone, tariff_type, volume, total_cost FROM Orders;";
		sqlite3_stmt* stmt;
		rc = sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr);

		if (rc != SQLITE_OK) {
			MessageBox::Show("Ошибка запроса к базе: " + gcnew String(sqlite3_errmsg(db)),
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			sqlite3_close(db);
			return;
		}

		try {
			// Очищаем текущие заказы
			/*company->GetOrders()->Clear();
			ordersTable->Rows->Clear();*/

			while (sqlite3_step(stmt) == SQLITE_ROW) {
				String^ clientName = UTF8ToString((const char*)sqlite3_column_text(stmt, 0));
				String^ clientPhone = UTF8ToString((const char*)sqlite3_column_text(stmt, 1));
				String^ tariffType = UTF8ToString((const char*)sqlite3_column_text(stmt, 2));
				double volume = sqlite3_column_double(stmt, 3);
				double totalCost = sqlite3_column_double(stmt, 4);

				// Находим или создаём клиента
				Client^ client = GetOrCreateClient(clientName, clientPhone);

				// Находим или создаём тариф (цена = totalCost / volume, но можно и фиксированную)
				double price = volume > 0 ? totalCost / volume : 0.0;
				Tariff^ tariff = GetOrCreateTariff(tariffType, price);

				// Создаём заказ
				Order^ order = gcnew Order(client, tariff, volume);
				company->GetOrders()->Add(order);

				// Добавляем в таблицу
				ordersTable->Rows->Add(clientName, clientPhone, tariffType, volume, totalCost, order);
			}

			MessageBox::Show("Заказы успешно загружены из базы данных.", "Успех",
				MessageBoxButtons::OK, MessageBoxIcon::Information);

		}
		catch (Exception^ ex) {
			MessageBox::Show("Ошибка при загрузке: " + ex->Message,
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}

		sqlite3_finalize(stmt);
		sqlite3_close(db);
	}
	private: array<String^>^ SafeSplitCSV(String^ line) {
		System::Collections::Generic::List<String^>^ items =
			gcnew System::Collections::Generic::List<String^>();

		bool inQuotes = false;
		System::Text::StringBuilder^ sb = gcnew System::Text::StringBuilder();

		for (int i = 0; i < line->Length; i++) {
			Char c = line[i];

			if (c == '\"') {
				// двойные кавычки ""
				if (inQuotes && i + 1 < line->Length && line[i + 1] == '\"') {
					sb->Append('\"');
					i++;
				}
				else {
					inQuotes = !inQuotes;
				}
			}
			else if (c == ';' && !inQuotes) {
				items->Add(sb->ToString());
				sb->Clear();
			}
			else {
				sb->Append(c);
			}
		}

		items->Add(sb->ToString());
		return items->ToArray();
	}

	private:
	// Convert System::String^ to std::string (UTF-8)
			std ::string StringToUTF8(System::String^ str) {
			if (str == nullptr) return "";
			array<Byte>^ bytes = System::Text::Encoding::UTF8->GetBytes(str);
			pin_ptr<Byte> pinned = &bytes[0];
			return std ::string((char*)pinned, bytes->Length);
		}

		// Convert UTF-8 std::string to System::String^
		System::String^ UTF8ToString(const char* utf8) {
			if (!utf8) return "";
			return gcnew System::String((char*)utf8, 0, (int)strlen(utf8), System::Text::Encoding::UTF8);
		}

	private: System::Void exportOrdersCSV_Click(System::Object^ sender, System::EventArgs^ e) {
		SaveFileDialog^ saveDialog = gcnew SaveFileDialog();
		saveDialog->Filter = "CSV файлы (*.csv)|*.csv";
		saveDialog->FileName = "Orders.csv";

		if (saveDialog->ShowDialog() != System::Windows::Forms::DialogResult::OK)
			return;

		try {
			System::Text::StringBuilder^ sb = gcnew System::Text::StringBuilder();

			// --- Записываем заголовки ---
			for (int col = 0; col < ordersTable->Columns->Count - 1; col++) {
				sb->Append(ordersTable->Columns[col]->ColumnName);

				if (col < ordersTable->Columns->Count - 2)
					sb->Append(";");
			}
			sb->AppendLine();

			// --- Записываем строки таблицы ---
			for (int i = 0; i < ordersTable->Rows->Count; i++) {

				for (int j = 0; j < ordersTable->Columns->Count - 1; j++) { // Пропускаем OrderObject
					System::String^ cell = ordersTable->Rows[i]->ItemArray[j]->ToString();



					// CSV безопасное значение — оборачиваем в кавычки
					cell = cell->Replace("\"", "\"\"");
					sb->Append("\"" + cell + "\"");

					if (j < ordersTable->Columns->Count - 2)
						sb->Append(";");
				}
				sb->AppendLine();
			}

			// --- Сохраняем файл ---
			System::IO::File::WriteAllText(saveDialog->FileName, sb->ToString(), System::Text::Encoding::UTF8);

			MessageBox::Show("CSV файл успешно сохранён:\n" + saveDialog->FileName,
				"Экспорт завершён", MessageBoxButtons::OK, MessageBoxIcon::Information);

		}
		catch (Exception^ ex) {
			MessageBox::Show("Ошибка при экспорте в CSV: " + ex->Message,
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
	private: System::Void importOrderCSV_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ openDialog = gcnew OpenFileDialog();
		openDialog->Filter = "CSV файлы (*.csv)|*.csv";

		if (openDialog->ShowDialog() != System::Windows::Forms::DialogResult::OK)
			return;

		try {
			array<String^>^ lines = System::IO::File::ReadAllLines(openDialog->FileName, System::Text::Encoding::UTF8);

			if (lines->Length < 2) {
				MessageBox::Show("CSV файл пуст или повреждён.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			// Пропускаем заголовок
			//ordersTable->Rows->Clear();

			for (int i = 1; i < lines->Length; i++) {

				String^ line = lines[i]->Trim();
				if (line->Length == 0) continue;

				// --- Разделение по ; с учётом кавычек ---
				array<String^>^ parts = SafeSplitCSV(line);

				if (parts->Length < 4)
					continue;

				String^ clientName = parts[0];
				String^ clientPhone = parts[1];
				String^ tariffType = parts[2];
				double volume = Double::Parse(parts[3]);
				double totalCost = Double::Parse(parts[4]);

				// --- Находим клиента ---
				clientName = parts[0];
				clientPhone = parts[1]; // читаем телефон
				Client^ client = GetOrCreateClient(clientName, clientPhone);

				// --- Находим тариф ---
				Tariff^ tariff = GetOrCreateTariff(tariffType, totalCost / volume);

				// --- Создаём заказ в компании ---
				Order^ newOrder = gcnew Order(client, tariff, volume);

				company->GetOrders()->Add(newOrder);

				// --- Добавляем строку в таблицу ---
				ordersTable->Rows->Add(
					clientName,
					clientPhone,
					tariffType,
					volume,
					totalCost,
					newOrder
				);
			}

			MessageBox::Show("CSV файл успешно загружен.", "Успех",
				MessageBoxButtons::OK, MessageBoxIcon::Information);

		}
		catch (Exception^ ex) {
			MessageBox::Show("Ошибка при загрузке CSV: " + ex->Message,
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
private: System::Void OrdersForm_Load(System::Object^ sender, System::EventArgs^ e) {
}
};

}