samples = [1,10*Fs];
[y,Fs] = audioread('Numb.wav',samples);         %16k, 8k, 4k
y16k = resample(y,1,3); %sound(y16k,16000);
y8k = resample(y,1,6); %sound(y8k,8000);
y4k = resample(y,1,12);%sound(y4k,4000);

figure 
y = y(:,1);
dt = 1/48000;
t = 0:dt:(length(y)*dt)-dt;
subplot(2,2,1)
plot(t,y); xlabel('Segundos'); ylabel('Amplitude');
title('48kHz')

y = y16k(:,1);
dt = 1/16000;
t = 0:dt:(length(y16k)*dt)-dt;
subplot(2,2,2)
plot(t,y16k); xlabel('Segundos'); ylabel('Amplitude');
title('16kHz')

y8k = y8k(:,1);
dt = 1/8000;
t8k = 0:dt:(length(y8k)*dt)-dt;
subplot(2,2,3)
plot(t8k,y8k); xlabel('Segundos'); ylabel('Amplitude');
title('8kHz')

y4k = y4k(:,1);
dt = 1/4000;
t4k = 0:dt:(length(y4k)*dt)-dt;
subplot(2,2,4)
plot(t4k,y4k); xlabel('Segundos'); ylabel('Amplitude');
title('4kHz')

