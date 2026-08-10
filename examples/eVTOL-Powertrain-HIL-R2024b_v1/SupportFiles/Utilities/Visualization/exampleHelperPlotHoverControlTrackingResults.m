function exampleHelperPlotHoverControlTrackingResults(simOut)
% exampleHelperPlotHoverControlTrackingResults plot results for hover
% analysis.

% Copyright 2023 The MathWorks, Inc.

%% Plot of Command vs Feedback
figure
subplot(3,1,1)
plot(simOut.PositionCmdFdbk.time,simOut.PositionCmdFdbk.signals.values(:,1),simOut.PositionCmdFdbk.time,simOut.PositionCmdFdbk.signals.values(:,4),'LineWidth',2)
grid
ylabel('X Position')
legend('Command','Feedback')
title('Command vs Feedback')

subplot(3,1,2)
plot(simOut.PositionCmdFdbk.time,simOut.PositionCmdFdbk.signals.values(:,2),simOut.PositionCmdFdbk.time,simOut.PositionCmdFdbk.signals.values(:,5),'LineWidth',2)
grid
ylabel('Y Position')

subplot(3,1,3)
plot(simOut.PositionCmdFdbk.time,simOut.PositionCmdFdbk.signals.values(:,3),simOut.PositionCmdFdbk.time,simOut.PositionCmdFdbk.signals.values(:,6),'LineWidth',2)
grid
xlabel('Time (sec)')
ylabel('Z Position')


%% Plot of Error
figure
subplot(3,1,1)
plot(simOut.PositionCmdFdbk.time,simOut.PositionCmdFdbk.signals.values(:,1)-simOut.PositionCmdFdbk.signals.values(:,4),'LineWidth',2)
grid
ylabel('X Position Error')
title('Command-Feedback Error')

subplot(3,1,2)
plot(simOut.PositionCmdFdbk.time,simOut.PositionCmdFdbk.signals.values(:,2)-simOut.PositionCmdFdbk.signals.values(:,5),'LineWidth',2)
grid
ylabel('Y Position Error')

subplot(3,1,3)
plot(simOut.PositionCmdFdbk.time,simOut.PositionCmdFdbk.signals.values(:,3)-simOut.PositionCmdFdbk.signals.values(:,6),'LineWidth',2)
grid
xlabel('Time (sec)')
ylabel('Z Position Error')

%% Plot in X-Y-Z
figure
plot3(simOut.PositionCmdFdbk.signals.values(:,1),-simOut.PositionCmdFdbk.signals.values(:,2),-simOut.PositionCmdFdbk.signals.values(:,3),'LineWidth',2)
hold on
plot3(simOut.PositionCmdFdbk.signals.values(:,4),-simOut.PositionCmdFdbk.signals.values(:,5),-simOut.PositionCmdFdbk.signals.values(:,6),'LineWidth',2)
hold off
grid
xlabel('North')
ylabel('West')
zlabel('Up')
legend('Command', 'Feedback')
end