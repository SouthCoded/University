package com.trafficmon;

import java.util.List;

public interface Operation {
     void operationsTakeAction(Vehicle vehicle, List<EventInterface> crossings);
}
