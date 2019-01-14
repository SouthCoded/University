package com.trafficmon;

import org.jmock.integration.junit4.JUnitRuleMockery;
import org.joda.time.DateTime;
import org.junit.Rule;
import org.junit.Test;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import static org.junit.Assert.assertEquals;

public class EventTest {

    public class ZoneTestingClass extends Event {
        public ZoneTestingClass(VehicleStatus a) {
            super(a);
        }
    }

    @Rule
    public JUnitRuleMockery context = new JUnitRuleMockery();
    ZoneTestingClass zoneTester = new ZoneTestingClass(Event.VehicleStatus.ENTERING);

    @Test
    public void testCorrectTimestamp() {
        DateTime currentDateTime = new DateTime();
        assertEquals(Math.round(currentDateTime.getMillis()), Math.round(zoneTester.getTime().getMillis()));
    }

    //TODO: Tried to create mock object of ZoneBoundaryInterface and set expectation of getVehicle to be called when vehicle is leaving but does not work.

}
