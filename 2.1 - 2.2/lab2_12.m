clear command
close all
clc

%2.1
f = 20;
T = 1/f;
dt = 0:0.001:3*T;

u = sin(2*pi*f*dt);

N = 0:length(dt)-1;
k = length(N);

Matrix = zeros(k, k);

for i = 1:k
    Matrix(i,:) = exp((1j*2*pi*(N*(i-1)))/k);
end


fh = zeros(k, k);
for i = 1 : length(fh)
    for j = 1 : length(fh)
        fh(i,j) = Matrix(j, i);
        fh(i, j) = real(fh(i,j)) - imag(fh(i,j))*1j;
    end
end 

figure(1);
subplot(3,1,1);

plot(dt, u);
title('Исходный сигнал');

subplot(3,1,2);

U = u * fh;
plot(abs(U));
title('Амплитудный спектр сигнала');

subplot(3,1,3);
u_rec = U * Matrix / k;
plot(dt, u);
hold on;
plot(dt, u_rec, 'r');
title('Сигнал после преобразования');


%2.2
%Линейность
f1 = 70;
u1 = sin(2*pi*f1*dt);
U1 = u1 * fh;

a = 5;
a1 = 7;

u_sum = a*u + a1*u1;
U_sum = u_sum * fh;

figure(2);
subplot(2,2,1);
plot(dt, u_sum);
title('Сумма сигналов');
subplot(2,2,2);
plot(abs(U_sum));
title('Спектр суммы сигналов');


subplot(2,2,3);
U4 = a1*U + a1*U1;
plot(abs(U4), 'r');
title('Сумма спектров');
subplot(2,2,4);
u4 = U4 * Matrix / k;
plot(dt, u4, 'r');
title('Сигнал суммы спектров');


%Сдвиг
tao = pi/f;
us = sin(2*pi*f*(dt-tao));
figure(3);
subplot(3,1,1)
plot(dt, us);
title('Сигнал со смещением');

Us = U .* exp(-1j*2*pi*tao*dt/k);
subplot(3,1,2)
plot(abs(Us));
title('Спектр со смещением');

us_recover = Us * Matrix / k;
subplot(3,1,3)
plot(dt, us_recover);
hold on;
plot(dt, us, 'r');
legend('Преобразованный', 'Исходный');
title('Сигнал после преобразований');
% На одном плоте + преобразование Фурье


%Равенство Парсеваля one=two
one = sum(abs(u) .* abs(u));
two = sum(abs(U) .* abs(U)) / k;
fprintf('one=%d, two=%d \none=two(истина)\n', one, two);


