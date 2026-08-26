% This script allows you to receive the UDP packets on the host PC and display the image without an 
% additional Simulink model. The 'udpport' functionality requires Instrument Control Toolbox™.

%% Check if the target machine is ready
if exist('tg','var') && strcmp(status(tg),'stopped')
    disp('Load the real-time application to the target machine first');
    return
elseif ~exist('tg','var')
    error("No target object named 'tg' found");
end

%% Initialize UDP ports on the host PC

udp1 = udpport("IPV4", "LocalHost", host_ip, "LocalPort", 25000);
udp2 = udpport("IPV4", "LocalHost", host_ip, "LocalPort", 25001);
udp3 = udpport("IPV4", "LocalHost", host_ip, "LocalPort", 25002);
udp4 = udpport("IPV4", "LocalHost", host_ip, "LocalPort", 25003);

%% Receive UDP packets from the target and display the image

% If the target machine is in loaded state, start it
if(strcmp(status(tg),'loaded'))
    tg.start;
    pause(0.5);
end

while(strcmp(status(tg),'running'))
    image_part1 = read(udp1, 62500, "uint8");
    image_part1 = reshape(image_part1,[250,250]);
    image_part2 = read(udp2, 62500, "uint8");
    image_part2 = reshape(image_part2,[250,250]);
    image_part3 = read(udp3, 62500, "uint8");
    image_part3 = reshape(image_part3,[250,250]);
    image_part4 = read(udp4, 62500, "uint8");
    image_part4 = reshape(image_part4,[250,250]);

    full_image = [image_part1, image_part2; image_part3, image_part4];
    imshow(full_image,[0,255]);

    pause(0.1)
end

%% Cleanup and release UDP ports
udp1.flush;
udp2.flush;
udp3.flush;
udp4.flush;
clear udp1 udp2 udp3 udp4;
clear image_part1 image_part2 image_part3 image_part4 full_image do_receive
