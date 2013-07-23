#include "obdpid.h"
#include <QDebug>

const QString ObdPid::DEFAULT_PID         = "0100";
const QString ObdPid::DEFAULT_NAME        = "No name";
const QString ObdPid::DEFAULT_DESCRIPTION = "No description";
const int ObdPid::DEFAULT_POLL_INTERVAL   = 100;
const QString ObdPid::DEFAULT_FORMULA     = "";
const int ObdPid::DEFAULT_NB_LINES        = 0;

ObdPid::ObdPid()
{
    setPid(DEFAULT_PID);
    setName(DEFAULT_NAME);
    setDescription(DEFAULT_DESCRIPTION);
    setPollInterval(DEFAULT_POLL_INTERVAL);
    setFormula(DEFAULT_FORMULA);
    setNbLines(DEFAULT_NB_LINES);
    pollTime = new QTime();
    pollTime->start();

    createFormulaInterpreter();
}

ObdPid::ObdPid(QString pid, QString name, QString description, QString unit, int pollInterval, QString formula, int nbLines)
{
    setPid(pid);
    setName(name);
    setDescription(description);
    setUnit(unit);
    setPollInterval(pollInterval);
    setFormula(formula);
    setNbLines(nbLines);    
    pollTime = new QTime();
    pollTime->start();

    createFormulaInterpreter();
}

ObdPid::~ObdPid()
{
    delete pollTime;
    delete evaluator;
}

double ObdPid::computeValue(QStringList data)
{
    QString lines = data.join("");
    lines.replace(QString(" "), QString(""));
    if(lines.at(0) == '4' && lines.at(1) == '1')
    {
        lines = lines.mid(4);

        char c;
        QString tmp;
        double value = 1;

        for(int i=0, j=0; i<lines.size(); i+=2, j++)
        {
            tmp.clear();
            tmp += lines.at(i);
            tmp += lines.at(i+1);
            c = j + 65;
            value = (double)(tmp.toInt(0,16));
            evaluator->setVariable(QString(c), value);
        }
        return evaluator->evaluate();
    }
    return -1.0;
}

void ObdPid::createFormulaInterpreter()
{
    evaluator = new ArithmeticEvaluator(formula);
}

QString ObdPid::getPid() const
{
    return pid;
}

void ObdPid::setPid(const QString &value)
{
    pid = value;
}

QString ObdPid::getDescription() const
{
    return description;
}

void ObdPid::setDescription(const QString &value)
{
    description = value;
}

QTime *ObdPid::getPollTime() const
{
    return pollTime;
}

void ObdPid::setPollTime(QTime *value)
{
    pollTime = value;
}

int ObdPid::getPollInterval() const
{
    return pollInterval;
}

void ObdPid::setPollInterval(int value)
{
    pollInterval = value;
}

QString ObdPid::getFormula() const
{
    return formula;
}

void ObdPid::setFormula(const QString &value)
{
    formula = value;
}

QString ObdPid::getUnit() const
{
    return unit;
}

void ObdPid::setUnit(const QString &value)
{
    unit = value;
}

int ObdPid::getNbLines() const
{
    return nbLines;
}

void ObdPid::setNbLines(int value)
{
    nbLines = value;
}

QString ObdPid::getName() const
{
    return name;
}

void ObdPid::setName(const QString &value)
{
    name = value;
}
