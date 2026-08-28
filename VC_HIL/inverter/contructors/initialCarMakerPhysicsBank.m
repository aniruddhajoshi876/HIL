function bank = initialCarMakerPhysicsBank()
%INITIALCARMAKERPHYSICSBANK Safe coherent-group retention state.
bank.pendingValues = zeros(4, 3);
bank.pendingSeen = false(1, 4);
bank.pendingCounter = uint8(0);
bank.hasPending = false;
bank.publishedValues = zeros(4, 3);
bank.publishedCounter = uint8(0);
bank.hasPublished = false;
bank.lastCompleteTickMs = uint32(0);
bank.acceptedCount = uint32(0);
bank.rejectedCount = uint32(0);
bank.lastRejectCode = uint8(0);
end
