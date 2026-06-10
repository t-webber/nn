module neuron_layer #(
    parameter int N = 3,
    parameter int P = 3,
    parameter int Width = 16
) (
    input  logic signed [Width-1:0] W[N][P],
    input  logic signed [Width-1:0] A[P],
    input  logic signed [Width-1:0] B[N],
    output logic signed [Width-1:0] Y[N]
);
    logic signed [Width-1:0] tmp;

    always_comb begin
        for (int i = 0; i < N; i++) begin
            tmp = B[i];
            for (int k = 0; k < P; k++) begin
                tmp += W[i][k] * A[k];
            end
            Y[i] = tmp >= 0 ? tmp : 0;
        end

    end


endmodule
