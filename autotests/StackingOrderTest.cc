// Own
#include "StackingOrder.h"
#include "Toplevel.h"

// Qt
#include <QScopedPointer>
#include <QtTest>

using namespace KWin;

class StackingOrderTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testAddRemove();
    void testReplace();
    void testConstrain();
    void testLayers();
    void testRestack();
    void testNoRestack();
};

void StackingOrderTest::testAddRemove()
{
    QScopedPointer<StackingOrder> stackingOrder(new StackingOrder());
    QScopedPointer<Toplevel> toplevelA(new Toplevel());
    QScopedPointer<Toplevel> toplevelB(new Toplevel());

    stackingOrder->add(toplevelA.data());
    stackingOrder->rebuild();
    QCOMPARE(stackingOrder->toplevels(), (ToplevelList { toplevelA.data() }));

    stackingOrder->add(toplevelB.data());
    stackingOrder->rebuild();
    QCOMPARE(stackingOrder->toplevels(), (ToplevelList { toplevelA.data(), toplevelB.data() }));

    stackingOrder->remove(toplevelA.data());
    stackingOrder->rebuild();
    QCOMPARE(stackingOrder->toplevels(), (ToplevelList { toplevelB.data() }));

    stackingOrder->remove(toplevelB.data());
    stackingOrder->rebuild();
    QCOMPARE(stackingOrder->toplevels(), ToplevelList());
}

void StackingOrderTest::testReplace()
{
    QScopedPointer<StackingOrder> stackingOrder(new StackingOrder());
    QScopedPointer<Toplevel> toplevelA(new Toplevel());
    QScopedPointer<Toplevel> toplevelB(new Toplevel());
    QScopedPointer<Toplevel> toplevelC(new Toplevel());

    stackingOrder->add(toplevelA.data());
    stackingOrder->add(toplevelB.data());
    stackingOrder->add(toplevelC.data());
    stackingOrder->rebuild();
    QCOMPARE(stackingOrder->toplevels(), (ToplevelList { toplevelA.data(), toplevelB.data(), toplevelC.data() }));

    QScopedPointer<Toplevel> toplevelD(new Toplevel());
    stackingOrder->replace(toplevelB.data(), toplevelD.data());
    stackingOrder->rebuild();
    QCOMPARE(stackingOrder->toplevels(), (ToplevelList { toplevelA.data(), toplevelD.data(), toplevelC.data() }));
}

void StackingOrderTest::testConstrain()
{
    QScopedPointer<StackingOrder> stackingOrder(new StackingOrder());
    QScopedPointer<Toplevel> toplevelA(new Toplevel());
    QScopedPointer<Toplevel> toplevelB(new Toplevel());
    QScopedPointer<Toplevel> toplevelC(new Toplevel());

    stackingOrder->add(toplevelA.data());
    stackingOrder->add(toplevelB.data());
    stackingOrder->add(toplevelC.data());
    stackingOrder->rebuild();
    QCOMPARE(stackingOrder->toplevels(), (ToplevelList { toplevelA.data(), toplevelB.data(), toplevelC.data() }));

    stackingOrder->constrain(toplevelC.data(), toplevelA.data());
    stackingOrder->rebuild();
    QCOMPARE(stackingOrder->toplevels(), (ToplevelList { toplevelB.data(), toplevelC.data(), toplevelA.data() }));
}

void StackingOrderTest::testLayers()
{
    QScopedPointer<StackingOrder> stackingOrder(new StackingOrder());
    QScopedPointer<Toplevel> toplevelA(new Toplevel());
    QScopedPointer<Toplevel> toplevelB(new Toplevel());
    QScopedPointer<Toplevel> toplevelC(new Toplevel());

    toplevelA->setLayer(AboveLayer);
    toplevelB->setLayer(NormalLayer);
    toplevelC->setLayer(BelowLayer);

    stackingOrder->add(toplevelA.data());
    stackingOrder->add(toplevelB.data());
    stackingOrder->add(toplevelC.data());
    stackingOrder->rebuild();
    QCOMPARE(stackingOrder->toplevels(), (ToplevelList { toplevelC.data(), toplevelB.data(), toplevelA.data() }));
}

void StackingOrderTest::testRestack()
{
    QScopedPointer<StackingOrder> stackingOrder(new StackingOrder());
    QScopedPointer<Toplevel> toplevelA(new Toplevel());
    QScopedPointer<Toplevel> toplevelB(new Toplevel());
    QScopedPointer<Toplevel> toplevelC(new Toplevel());

    stackingOrder->add(toplevelA.data());
    stackingOrder->add(toplevelB.data());
    stackingOrder->add(toplevelC.data());
    stackingOrder->rebuild();
    QCOMPARE(stackingOrder->toplevels(), (ToplevelList { toplevelA.data(), toplevelB.data(), toplevelC.data() }));

    stackingOrder->restack(toplevelC.data(), toplevelA.data());
    stackingOrder->rebuild();
    QCOMPARE(stackingOrder->toplevels(), (ToplevelList { toplevelB.data(), toplevelC.data(), toplevelA.data() }));
}

void StackingOrderTest::testNoRestack()
{
    QScopedPointer<StackingOrder> stackingOrder(new StackingOrder());
    QScopedPointer<Toplevel> toplevelA(new Toplevel());
    QScopedPointer<Toplevel> toplevelB(new Toplevel());
    QScopedPointer<Toplevel> toplevelC(new Toplevel());

    stackingOrder->add(toplevelA.data());
    stackingOrder->add(toplevelB.data());
    stackingOrder->add(toplevelC.data());
    stackingOrder->rebuild();
    QCOMPARE(stackingOrder->toplevels(), (ToplevelList { toplevelA.data(), toplevelB.data(), toplevelC.data() }));

    stackingOrder->restack(toplevelA.data(), toplevelC.data());
    stackingOrder->rebuild();
    QCOMPARE(stackingOrder->toplevels(), (ToplevelList { toplevelA.data(), toplevelB.data(), toplevelC.data() }));
}

QTEST_GUILESS_MAIN(StackingOrderTest)
#include "StackingOrderTest.moc"
