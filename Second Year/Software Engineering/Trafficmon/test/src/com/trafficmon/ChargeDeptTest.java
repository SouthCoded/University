package com.trafficmon;

import org.junit.Before;
import org.junit.Test;

import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.*;

public class ChargeDeptTest {

    private CalculateChargeBehavior chargingDepartment;
    private List<EventInterface> crossings;

//  Tests adapted for functionality to work with calculateChargeByDuration()

    @Before
    public void setUp(){
       chargingDepartment = new CalculateByDuration();
       crossings = new ArrayList<>();
    }

    @Test
    public void testEdgeCaseOfChargingTwiceIfEnteringAndExitingInTheSameHour() {
        FakeEvent Entry = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        Entry.setHourTime(11);
        FakeEvent Exit = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        Exit.setHourTime(11);


        FakeEvent Entry2 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        Entry2.setHourTime(12);
        FakeEvent Exit2 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        Exit2.setHourTime(13);

        crossings.add(Entry);
        crossings.add(Exit);

        crossings.add(Entry2);
        crossings.add(Exit2);

        BigDecimal charge = chargingDepartment.calculateCharge(crossings);

        assertEquals(6, charge.intValue());
    }

    @Test
    public void testChargeForTimeInZoneByDurationMoreThanMaxHours() {
        FakeEvent Entry = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        Entry.setHourTime(10);
        crossings.add(Entry);

        FakeEvent Exit = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        Exit.setHourTime(15);
        crossings.add(Exit);

        BigDecimal charge = chargingDepartment.calculateCharge(crossings);

        assertEquals(12,charge.intValue());
    }

    @Test
    public void testChargeForTimeInZoneByDurationMoreThanMaxHoursAfterTwo() {
        FakeEvent Entry = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        Entry.setHourTime(14);
        crossings.add(Entry);

        FakeEvent Exit = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        Exit.setHourTime(20);
        crossings.add(Exit);

        BigDecimal charge = chargingDepartment.calculateCharge(crossings);

        assertEquals(12,charge.intValue());
    }

    //FIXED -- FIXME: We must change implementation of Event as we cannot assign both the time and if its Entry or Exit hence cannot adjust time to be 2pm or 2am of Event.

    @Test
    public void testChargeForTimeInZoneByDurationBeforeCertainTime() {
        FakeEvent eventEntry = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry.setHourTime(11); //Entry at 11:00

        crossings.add(eventEntry);

        FakeEvent eventExit = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit.setHourTime(14); //Leave at 14:00

        crossings.add(eventExit);

        BigDecimal charge = chargingDepartment.calculateCharge(crossings);

        assertEquals(6,charge.intValue());
    }

    @Test
    public void testChargeForTimeInZoneByDurationAfterCertainTime() {
        FakeEvent eventEntry = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry.setHourTime(15);
        FakeEvent eventExit = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit.setHourTime(16);

        crossings.add(eventEntry); //Entry at 14:00
        crossings.add(eventExit); //Leave at 16:00

        BigDecimal charge = chargingDepartment.calculateCharge(crossings);

        assertEquals(4,charge.intValue());
    }

    @Test
    public void testChargeForTimeInZoneByDurationBeforeCertainTimeNotChargedTwice() {
        FakeEvent eventEntry1 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry1.setHourTime(11);
        FakeEvent eventExit1 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit1.setHourTime(12);
        FakeEvent eventEntry2 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry2.setHourTime(13);
        FakeEvent eventExit2 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit2.setHourTime(14);

        crossings.add(eventEntry1); //Entry at 11:00
        crossings.add(eventExit1);
        crossings.add(eventEntry2);
        crossings.add(eventExit2);

        BigDecimal charge = chargingDepartment.calculateCharge(crossings);

        assertEquals(6,charge.intValue());
    }

    @Test
    public void testChargeForTimeInZoneByDurationAfterCertainTimeNotChargedTwice() {
        FakeEvent eventEntry1 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry1.setHourTime(14);

        FakeEvent eventExit1 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit1.setHourTime(16);

        FakeEvent eventEntry2 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry2.setHourTime(17);

        FakeEvent eventExit2 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit2.setHourTime(18);

        crossings.add(eventEntry1); //Entry at 14:00
        crossings.add(eventExit1);
        crossings.add(eventEntry2);
        crossings.add(eventExit2); //Exit at 18:00

        BigDecimal charge = chargingDepartment.calculateCharge(crossings);

        assertEquals(4,charge.intValue());
    }


    @Test
    public void testChargeBothTimeZone() {
        FakeEvent eventEntry1 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry1.setHourTime(10);

        FakeEvent eventExit1 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit1.setHourTime(11);

        FakeEvent eventEntry2 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry2.setHourTime(17);

        FakeEvent eventExit2 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit2.setHourTime(18);

        crossings.add(eventEntry1); //Entry at 10:00
        crossings.add(eventExit1);
        crossings.add(eventEntry2);
        crossings.add(eventExit2); //Exit at 18:00

        BigDecimal charge = chargingDepartment.calculateCharge(crossings);

        assertEquals(10, charge.intValue());
    }

    @Test
    public void testChargeMinuteBeforeTwoLessThanHour(){
        FakeEvent eventEntry1 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry1.setHourTime(10);

        FakeEvent eventExit1 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit1.setHourTime(11);
        // Now it is 50 mins difference.
        eventExit1.setPlusMinutes(-10);

        crossings.add(eventEntry1); //Entry at 14:00
        crossings.add(eventExit1);
        BigDecimal charge = chargingDepartment.calculateCharge(crossings);

        assertEquals(6, charge.intValue());
    }

    @Test
    public void testChargeMinuteAfterTwoLessThanHour(){
        FakeEvent eventEntry1 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry1.setHourTime(17);

        FakeEvent eventExit1 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit1.setHourTime(18);
        // Now it is 50 mins difference.
        eventExit1.setPlusMinutes(-10);

        crossings.add(eventEntry1); //Entry at 14:00
        crossings.add(eventExit1);
        BigDecimal charge = chargingDepartment.calculateCharge(crossings);

        assertEquals(4, charge.intValue());
    }


    @Test
    public void testChargeMinuteBeforeTwoLessThanFour(){
        FakeEvent eventEntry1 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry1.setHourTime(10);

        FakeEvent eventExit1 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit1.setHourTime(14);
        // Now it is 3 Hr 50 mins difference.
        eventExit1.setPlusMinutes(-10);

        crossings.add(eventEntry1); //Entry at 14:00
        crossings.add(eventExit1);
        BigDecimal charge = chargingDepartment.calculateCharge(crossings);

        assertEquals(6, charge.intValue());
    }

    @Test
    public void testChargeMinuteAfterTwoLessThanFour(){
        FakeEvent eventEntry1 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry1.setHourTime(17);

        FakeEvent eventExit1 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit1.setHourTime(21);
        // Now it is 3 Hr 50 mins difference.
        eventExit1.setPlusMinutes(-10);

        crossings.add(eventEntry1); //Entry at 14:00
        crossings.add(eventExit1);
        BigDecimal charge = chargingDepartment.calculateCharge(crossings);

        assertEquals(4, charge.intValue());
    }


    @Test
    public void testChargeMinuteBeforeTwoAbitMoreFour(){
        FakeEvent eventEntry1 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry1.setHourTime(9);

        FakeEvent eventExit1 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit1.setHourTime(13);
        // Now it is 4 Hr 10 mins difference.
        eventExit1.setPlusMinutes(10);

        crossings.add(eventEntry1); //Entry at 14:00
        crossings.add(eventExit1);
        BigDecimal charge = chargingDepartment.calculateCharge(crossings);

        assertEquals(12, charge.intValue());
    }

    @Test
    public void testChargeMinuteAfterTwoAbitMoreFour(){
        FakeEvent eventEntry1 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry1.setHourTime(17);

        FakeEvent eventExit1 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit1.setHourTime(21);
        // Now it is 4 Hr 10 mins difference.
        eventExit1.setPlusMinutes(10);

        crossings.add(eventEntry1); //Entry at 14:00
        crossings.add(eventExit1);
        BigDecimal charge = chargingDepartment.calculateCharge(crossings);

        assertEquals(12, charge.intValue());
    }

    @Test
    public void testSameTimeEntryExit(){
        FakeEvent eventEntry1 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry1.setHourTime(14);

        FakeEvent eventExit1 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit1.setHourTime(14);

        crossings.add(eventEntry1); //Entry at 14:00
        crossings.add(eventExit1); //Exit within 14:00
        BigDecimal charge = chargingDepartment.calculateCharge(crossings);

        //Charged as if after 14:00
        assertEquals(4, charge.intValue());
    }

    @Test
    public void testSameTimeEntryExitBeforeTwo(){
        FakeEvent eventEntry1 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry1.setHourTime(10);

        FakeEvent eventExit1 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit1.setHourTime(10);

        crossings.add(eventEntry1); //Entry at 10:00
        crossings.add(eventExit1); //Exit within 10:00
        BigDecimal charge = chargingDepartment.calculateCharge(crossings);

        //Charged as if after 10:00
        assertEquals(6, charge.intValue());
    }

    @Test
    public void testInBetweenZones(){
        FakeEvent eventEntry1 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry1.setHourTime(13);

        FakeEvent eventExit1 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit1.setHourTime(16);

        crossings.add(eventEntry1); //Entry at 1:00
        crossings.add(eventExit1); //Exit 4:00
        BigDecimal charge = chargingDepartment.calculateCharge(crossings);

        //Charged as if after 14:00
        assertEquals(6, charge.intValue());
    }

    @Test
    public void testEntryExitThenEntryExitAfterFourHoursChargedTwiceBefore(){
        FakeEvent eventEntry1 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry1.setHourTime(5);

        FakeEvent eventExit1 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit1.setHourTime(6);

        FakeEvent eventEntry2 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry2.setHourTime(11);

        FakeEvent eventExit2 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit2.setHourTime(12);

        crossings.add(eventEntry1);
        crossings.add(eventExit1);
        crossings.add(eventEntry2);
        crossings.add(eventExit2);

        BigDecimal charge = chargingDepartment.calculateCharge(crossings);

        assertEquals(12,charge.intValue());

    }

    @Test
    public void testEntryExitThenEntryExitAfterFourHoursChargedTwiceAfter(){
        FakeEvent eventEntry1 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry1.setHourTime(14);

        FakeEvent eventExit1 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit1.setHourTime(15);

        FakeEvent eventEntry2 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry2.setHourTime(19);

        FakeEvent eventExit2 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit2.setHourTime(20);

        crossings.add(eventEntry1);
        crossings.add(eventExit1);
        crossings.add(eventEntry2);
        crossings.add(eventExit2);

        BigDecimal charge = chargingDepartment.calculateCharge(crossings);

        assertEquals(8,charge.intValue());

    }

    @Test
    public void testEntryExitThenEntryExitAfterFourHoursChargedInBetween(){
        FakeEvent eventEntry1 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry1.setHourTime(13);

        FakeEvent eventExit1 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit1.setHourTime(14);

        FakeEvent eventEntry2 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry2.setHourTime(19);

        FakeEvent eventExit2 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit2.setHourTime(20);

        crossings.add(eventEntry1);
        crossings.add(eventExit1);
        crossings.add(eventEntry2);
        crossings.add(eventExit2);

        BigDecimal charge = chargingDepartment.calculateCharge(crossings);

        assertEquals(10,charge.intValue());
    }

    @Test
    public void testEntryExitThenEntryExitAfterFourHoursChargedInBetweenMoreThanFourHours(){
        FakeEvent eventEntry1 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry1.setHourTime(8);

        FakeEvent eventExit1 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit1.setHourTime(14);

        FakeEvent eventEntry2 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry2.setHourTime(19);

        FakeEvent eventExit2 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit2.setHourTime(20);

        crossings.add(eventEntry1);
        crossings.add(eventExit1);
        crossings.add(eventEntry2);
        crossings.add(eventExit2);

        BigDecimal charge = chargingDepartment.calculateCharge(crossings);

        assertEquals(12,charge.intValue());
    }

    @Test
    public void testEntryExitThenEntryExitAfterFourHoursBeforeThreeTimes(){
        FakeEvent eventEntry1 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry1.setHourTime(1);

        FakeEvent eventExit1 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit1.setHourTime(2);

        FakeEvent eventEntry2 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry2.setHourTime(7);

        FakeEvent eventExit2 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit2.setHourTime(8);

        FakeEvent eventEntry3 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry3.setHourTime(12);

        FakeEvent eventExit3 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit3.setHourTime(13);

        crossings.add(eventEntry1);
        crossings.add(eventExit1);
        crossings.add(eventEntry2);
        crossings.add(eventExit2);
        crossings.add(eventEntry3);
        crossings.add(eventExit3);

        BigDecimal charge = chargingDepartment.calculateCharge(crossings);

        assertEquals(18,charge.intValue());
    }

    @Test
    public void testEntryExitThenEntryExitAfterFourHoursAfterThreeTimes(){
        FakeEvent eventEntry1 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry1.setHourTime(14);

        FakeEvent eventExit1 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit1.setHourTime(15);

        FakeEvent eventEntry2 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry2.setHourTime(19);

        FakeEvent eventExit2 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit2.setHourTime(19);

        FakeEvent eventEntry3 = new FakeEvent(EventInterface.VehicleStatus.ENTERING);
        eventEntry3.setHourTime(23);

        FakeEvent eventExit3 = new FakeEvent(EventInterface.VehicleStatus.EXITING);
        eventExit3.setHourTime(23);

        crossings.add(eventEntry1);
        crossings.add(eventExit1);
        crossings.add(eventEntry2);
        crossings.add(eventExit2);
        crossings.add(eventEntry3);
        crossings.add(eventExit3);

        BigDecimal charge = chargingDepartment.calculateCharge(crossings);

        assertEquals(12,charge.intValue());
    }


    //FIXED -- FIXME: Does not work when entry/exit have same times.
}