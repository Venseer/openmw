#include "landcreator.hpp"

#include <limits>

#include "../../model/world/land.hpp"

namespace CSVWorld
{
    LandCreator::LandCreator(CSMWorld::Data& data, QUndoStack& undoStack, const CSMWorld::UniversalId& id)
        : GenericCreator(data, undoStack, id)
        , mXLabel(nullptr)
        , mYLabel(nullptr)
        , mX(nullptr)
        , mY(nullptr)
    {
        const int MaxInt = std::numeric_limits<int>::max();
        const int MinInt = std::numeric_limits<int>::min();

        setManualEditing(false);

        mXLabel = new QLabel("X: ");
        mX = new QSpinBox();
        mX->setMinimum(MinInt);
        mX->setMaximum(MaxInt);
        insertBeforeButtons(mXLabel, false);
        insertBeforeButtons(mX, true);

        mYLabel = new QLabel("Y: ");
        mY = new QSpinBox();
        mY->setMinimum(MinInt);
        mY->setMaximum(MaxInt);
        insertBeforeButtons(mYLabel, false);
        insertBeforeButtons(mY, true);

        connect (mX, SIGNAL(valueChanged(int)), this, SLOT(coordChanged(int)));
        connect (mY, SIGNAL(valueChanged(int)), this, SLOT(coordChanged(int)));
    }

    void LandCreator::cloneMode(const std::string& originId, const CSMWorld::UniversalId::Type type)
    {
        GenericCreator::cloneMode(originId, type);

        int x = 0, y = 0;
        CSMWorld::Land::parseUniqueRecordId(originId, x, y);

        mX->setValue(x);
        mY->setValue(y);
    }

    void LandCreator::focus()
    {
        mX->setFocus();
    }

    void LandCreator::reset()
    {
        GenericCreator::reset();
        mX->setValue(0);
        mY->setValue(0);
    }

    std::string LandCreator::getErrors() const
    {
        if (getData().getLand().searchId(getId()) >= 0)
            return "A land with that name already exists.";

        return "";
    }

    std::string LandCreator::getId() const
    {
        return CSMWorld::Land::createUniqueRecordId(mX->value(), mY->value());
    }

    void LandCreator::coordChanged(int value)
    {
        update();
    }
}
