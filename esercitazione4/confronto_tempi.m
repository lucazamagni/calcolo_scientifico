% Vettore delle dimensioni: 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192
% Vettore dei tempi del bubblesort: 1.4001e-05 7.12e-07 1.172e-06 3.598e-06 1.2747e-05 4.6601e-05 0.000184561 0.000890827 0.00351343 0.0131466 0.0518655 0.246116 1.0794
% Vettore dei tempi del insertionsort: 4.91e-07 3.71e-07 6.51e-07 1.493e-06 4.279e-06 1.373e-05 6.8158e-05 0.000198582 0.000761465 0.00313223 0.0118362 0.0617262 0.204089
% Vettore dei tempi del selectionsort: 4.71e-07 5.51e-07 1.072e-06 2.566e-06 8.067e-06 2.7499e-05 9.8644e-05 0.000369914 0.00149593 0.00593843 0.0247208 0.0940776 0.582836
% Vettore dei tempi del std::sort: 7.92e-07 8.72e-07 1.043e-06 2.305e-06 7.406e-06 1.4651e-05 3.3533e-05 7.5755e-05 0.000167905 0.000356976 0.000776007 0.00197382 0.00513495

N=[2 4 8 16 32 64 128 256 512 1024 2048 4096 8192];
t_bubble=[1.4001e-05 7.12e-07 1.172e-06 3.598e-06 1.2747e-05 4.6601e-05 0.000184561 0.000890827 0.00351343 0.0131466 0.0518655 0.246116 1.0794];
t_insertion=[4.91e-07 3.71e-07 6.51e-07 1.493e-06 4.279e-06 1.373e-05 6.8158e-05 0.000198582 0.000761465 0.00313223 0.0118362 0.0617262 0.204089];
t_selection=[4.71e-07 5.51e-07 1.072e-06 2.566e-06 8.067e-06 2.7499e-05 9.8644e-05 0.000369914 0.00149593 0.00593843 0.0247208 0.0940776 0.582836];
t_stdsort=[7.92e-07 8.72e-07 1.043e-06 2.305e-06 7.406e-06 1.4651e-05 3.3533e-05 7.5755e-05 0.000167905 0.000356976 0.000776007 0.00197382 0.00513495];

loglog(N, t_bubble, '-o', 'LineWidth', 2); hold on;
loglog(N, t_insertion, '-s', 'LineWidth', 2);
loglog(N, t_selection, '-d', 'LineWidth', 2);
loglog(N, t_stdsort, '-x', 'LineWidth', 2);

grid on;
xlabel('Dimensione del Vettore (N) [log]');
ylabel('Tempo di esecuzione (secondi) [log]');
title('Confronto Algoritmi di Sorting (Scala Log-Log)');
legend('bubblesort', 'insertionsort', 'selectionsort', 'std::sort','Location', 'northwest');
