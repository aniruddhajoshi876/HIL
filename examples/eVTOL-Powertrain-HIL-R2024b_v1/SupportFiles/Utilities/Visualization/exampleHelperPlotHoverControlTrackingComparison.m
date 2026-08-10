function exampleHelperPlotHoverControlTrackingComparison(simOutBaseline,simOutTuned)
% exampleHelperPlotHoverControlTrackingComparison plot results for hover
% control analysis.

% Copyright 2023 The MathWorks, Inc.

%% Plot of Command vs Feedback
figure
subplot(3,1,1)
plot(simOutBaseline.PositionCmdFdbk.time,simOutBaseline.PositionCmdFdbk.signals.values(:,4),'LineWidth',2)
hold on
plot(simOutTuned.PositionCmdFdbk.time,simOutTuned.PositionCmdFdbk.signals.values(:,4),'LineWidth',2)
hold off
grid
ylabel('X Position')
legend('Baseline','Autotuned')
title('Command vs Feedback')

subplot(3,1,2)
plot(simOutBaseline.PositionCmdFdbk.time,simOutBaseline.PositionCmdFdbk.signals.values(:,5),'LineWidth',2)
hold on
plot(simOutTuned.PositionCmdFdbk.time,simOutTuned.PositionCmdFdbk.signals.values(:,5),'LineWidth',2)
hold off
grid
ylabel('Y Position')

subplot(3,1,3)
plot(simOutBaseline.PositionCmdFdbk.time,simOutBaseline.PositionCmdFdbk.signals.values(:,6),'LineWidth',2)
hold on
plot(simOutTuned.PositionCmdFdbk.time,simOutTuned.PositionCmdFdbk.signals.values(:,6),'LineWidth',2)
hold off
grid
xlabel('Time (sec)')
ylabel('Z Position')


%% Plot of Error
figure
subplot(3,1,1)
plot(simOutBaseline.PositionCmdFdbk.time,simOutBaseline.PositionCmdFdbk.signals.values(:,1)-simOutBaseline.PositionCmdFdbk.signals.values(:,4),'LineWidth',2)
hold on
plot(simOutTuned.PositionCmdFdbk.time,simOutTuned.PositionCmdFdbk.signals.values(:,1)-simOutTuned.PositionCmdFdbk.signals.values(:,4),'LineWidth',2)
hold off
grid
ylabel('X Position Error')
title('Baseline','Autotuned')
title('Command-Feedback Error')

subplot(3,1,2)
plot(simOutBaseline.PositionCmdFdbk.time,simOutBaseline.PositionCmdFdbk.signals.values(:,2)-simOutBaseline.PositionCmdFdbk.signals.values(:,5),'LineWidth',2)
hold on
plot(simOutTuned.PositionCmdFdbk.time,simOutTuned.PositionCmdFdbk.signals.values(:,2)-simOutTuned.PositionCmdFdbk.signals.values(:,5),'LineWidth',2)
hold off
grid
ylabel('Y Position Error')

subplot(3,1,3)
plot(simOutBaseline.PositionCmdFdbk.time,simOutBaseline.PositionCmdFdbk.signals.values(:,3)-simOutBaseline.PositionCmdFdbk.signals.values(:,6),'LineWidth',2)
hold on
plot(simOutTuned.PositionCmdFdbk.time,simOutTuned.PositionCmdFdbk.signals.values(:,3)-simOutTuned.PositionCmdFdbk.signals.values(:,6),'LineWidth',2)
hold off
grid
xlabel('Time (sec)')
ylabel('Z Position Error')

%% Plot in X-Y-Z
figure
plot3(simOutBaseline.PositionCmdFdbk.signals.values(:,4),-simOutBaseline.PositionCmdFdbk.signals.values(:,5),-simOutBaseline.PositionCmdFdbk.signals.values(:,6),'LineWidth',2)
hold on
plot3(simOutTuned.PositionCmdFdbk.signals.values(:,4),-simOutTuned.PositionCmdFdbk.signals.values(:,5),-simOutTuned.PositionCmdFdbk.signals.values(:,6),'LineWidth',2)
hold off
grid
xlabel('North')
ylabel('West')
zlabel('Up')
legend('Baseline', 'Autotuned')
end