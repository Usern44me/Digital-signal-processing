F = 10;
Fd = 10*F;
Td = 1/Fd;
t = 0:Td:(10/F);


dis = zeros(length(t),1);
for i = 1:length(t)
    dis(i) = sin(F*t(i) + pi/3);
end



res_t = 0:0.0001:(10/F);
res_u = zeros(length(res_t),1);
for i = 1:length(res_t)
    for k = 1:length(dis)
		res_u(i) = res_u(i) + dis(k) * sin(pi*(res_t(i)/Td - k + 1))/(pi*(res_t(i)/Td - k + 1));
    end
end

source = zeros(length(res_t),1);
for i = 1:length(res_t)
    source(i) = sin(F*res_t(i) + pi/3);
end
plot(res_t, res_u);
hold on;
plot(res_t, source);