#include "VectSpecs.h"
#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>


// Conventions
const QString VectSpecs::analysis_id_str = "vect";

// Constructors
VectSpecs::VectSpecs(QJsonDocument json_specs_doc)
{
    // Get main object from document
    QJsonObject json_specs = json_specs_doc.object();
    // Initialize from specs
    this->model_name      = json_specs.value(QString("model_name")).toString();
    this->model_file_path = json_specs.value(QString("model_mo_path")).toString();
    this->percentage      = json_specs.value(QString("percentage")).toDouble();
    this->start_time      = json_specs.value(QString("start_time")).toDouble();
    this->stop_time       = json_specs.value(QString("stop_time")).toDouble();
    this->epsilon         = json_specs.value(QString("epsilon")).toDouble();
    this->target_var      = json_specs.value(QString("target_var_name")).toString();
    // Get parameters QVariant list
    QList<QVariant> parametersQVariant = json_specs.value(QString("parameters_to_perturb")).toArray().toVariantList();
    // Transform from list of QVariant to list of QString
    this->parameters_to_perturb = fromListOfVariantToListOfStr(parametersQVariant);
    // Get optimization type
    QString max_or_min  = json_specs.value(QString("max_or_min")).toString();
    this->maximize = ifMaximizationFromMaxOrMinStr(max_or_min);}
VectSpecs::VectSpecs( QString model_file_path, QString model_name, bool maximize,
               QStringList parameters_to_perturb, double epsilon, double percentage, double start_time,
               double stop_time, QString target_var):
    model_file_path(model_file_path),
    model_name(model_name),
    maximize(maximize),
    parameters_to_perturb(parameters_to_perturb),
    epsilon(epsilon),
    percentage(percentage),
    start_time(start_time),
    stop_time(stop_time),
    target_var(target_var)
{
    // Do nothing else for now
}

// Methods
QJsonDocument VectSpecs::toJson()
{
    // Initialize JSON root object
    QJsonObject json_specs;
    // Specify analysis type
    json_specs["analysis_type"]         = this->analysis_id_str;
    // Add specs to json
    json_specs["model_name"]            = this->model_name;
    json_specs["model_mo_path"]         = this->model_file_path;
    json_specs["start_time"]            = this->start_time;
    json_specs["stop_time"]             = this->stop_time;
    json_specs["percentage"]            = this->percentage;
    json_specs["epsilon"]               = this->epsilon;
    json_specs["target_var_name"]       = this->target_var;
    json_specs["parameters_to_perturb"] = QJsonArray::fromStringList(this->parameters_to_perturb);
    QString optim_type_string           = optimTypeString(this->maximize);
    json_specs["max_or_min"]            = optim_type_string;
    // Initialize JSON doc from JSON object
    QJsonDocument json_specs_doc(json_specs);

    return json_specs_doc;
}


// Auxs
QList<QString> VectSpecs::fromListOfVariantToListOfStr(QList<QVariant> listOfQVariant)
{
    QList<QString> listOfStr;
    foreach (QVariant objQVariant, listOfQVariant) {
        QString objStr = objQVariant.toString();
        listOfStr.append(objStr);
    }
    return listOfStr;
}

QString VectSpecs::optimTypeString(bool maximize)
{
    QString optim_type_string;
    if(maximize) optim_type_string = "max";
    else         optim_type_string = "min";
    return optim_type_string;
}

bool VectSpecs::ifMaximizationFromMaxOrMinStr(QString max_or_min)
{
    bool maximize = false;
    if(max_or_min == "max") maximize = true;
    else if(max_or_min == "min") maximize = false;
    else
    {
        // TODO: tirar error
    }

    return maximize;
}
