`timescale 1ns / 1ps

module laplacian
(
 CLK, RESET,
 D02IN, D01IN, D00IN, // Upper Line
 D12IN, D11IN, D10IN, // Middle Line
 D22IN, D21IN, D20IN, // Under Line
 Dout
);

 input CLK, RESET;
 input [23:0] D02IN,D01IN,D00IN;
 input [23:0] D12IN,D11IN,D10IN;
 input [23:0] D22IN,D21IN,D20IN;
 output reg [23:0] Dout;
 reg signed [10:0] tmp;

 //Preprocess for GrayScaling
 reg [10:0] gray00, gray01, gray02;
 reg [10:0] gray10, gray11, gray12;
 reg [10:0] gray20, gray21, gray22;

 always @( posedge CLK ) begin
   if(~RESET) begin gray00 <= 0; gray01 <= 0; gray02 <= 0;
                    gray00 <= 0; gray01 <= 0; gray02 <= 0;
                    gray00 <= 0; gray01 <= 0; gray02 <= 0; end
   else begin
      gray00 <= ((D00IN[23:16]/3) + (D00IN[15:8]/3) + (D00IN[7:0]/3));
      gray01 <= ((D01IN[23:16]/3) + (D01IN[15:8]/3) + (D01IN[7:0]/3));
      gray02 <= ((D02IN[23:16]/3) + (D02IN[15:8]/3) + (D02IN[7:0]/3));
      gray10 <= ((D10IN[23:16]/3) + (D10IN[15:8]/3) + (D10IN[7:0]/3));
      gray11 <= ((D11IN[23:16]/3) + (D11IN[15:8]/3) + (D11IN[7:0]/3));
      gray12 <= ((D12IN[23:16]/3) + (D12IN[15:8]/3) + (D12IN[7:0]/3));
      gray20 <= ((D20IN[23:16]/3) + (D20IN[15:8]/3) + (D20IN[7:0]/3));
      gray21 <= ((D21IN[23:16]/3) + (D21IN[15:8]/3) + (D21IN[7:0]/3));
      gray22 <= ((D22IN[23:16]/3) + (D22IN[15:8]/3) + (D22IN[7:0]/3));
        end
 end


 always @( posedge CLK ) begin
   if(~RESET) begin tmp <= 0; end
   else
     begin tmp<=(gray00+gray01+gray02+gray10+gray12+gray20+gray21+gray22-(gray11<<3)); end
 end

 always @( posedge CLK ) begin
   if(~RESET) begin Dout <= 0; end
   else begin
     Dout <= (tmp>255) ? 24'hffffff : (tmp<0) ? 24'h000000 : {tmp[7:0],tmp[7:0],tmp[7:0]};
        end
 end

 endmodule
