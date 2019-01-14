package com.trafficmon;

import java.math.BigDecimal;
import java.util.List;

public interface CalculateChargeBehavior {
    BigDecimal calculateCharge(List<EventInterface> crossings);
}
