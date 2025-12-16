#pragma once
using namespace System;

public enum class CargoType {
    General,
    Fragile,
    Hazardous,
    Refrigerated
};

ref class Tariff {
public:
    property CargoType Type;
    property double PricePerUnit;

    Tariff(CargoType type, double price) {
        Type = type;
        PricePerUnit = price;
    }

    // Для DataGridView
    property String^ TypeString {
        String^ get() {
            switch (Type) {
            case CargoType::General: return "Интернет";
            case CargoType::Fragile: return "Вода";
            case CargoType::Hazardous: return "Ремонт";
            case CargoType::Refrigerated: return "Отопление";
            default: return "Unknown";
            }
        }
    }
};
