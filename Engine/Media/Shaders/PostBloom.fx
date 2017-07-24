//====================================================
// Post Bloom (ps 1.4)
// By EVOLVED
//====================================================

//--------------
// tweaks
//--------------
   float ViewScaleX;
   float ViewScaleY;
   float BlurOffset = 0.008f;
   float GlowIntensity = 1.0f;
   float MotionBlur = 0.4f;

//--------------
// Textures
//--------------
   texture RenderColorTX 
      <
      	string Name = " ";
      >;
   sampler2D RenderColor=sampler_state 
      {
	Texture=<RenderColorTX>;
     	ADDRESSU=CLAMP;
        ADDRESSV=CLAMP;
        ADDRESSW=CLAMP;
	MagFilter = None;
	MinFilter = None;
	MipFilter = None;
      };
   texture DownColorTX 
      <
      	string Name = " ";
      >;
   sampler2D DownColor=sampler_state 
      {
	Texture=<DownColorTX>;
     	ADDRESSU=CLAMP;
        ADDRESSV=CLAMP;
        ADDRESSW=CLAMP;
      };
   texture GlowHColorTX 
      <
      	string Name = " ";
      >;
   sampler2D GlowHColor=sampler_state 
      {
	Texture=<GlowHColorTX>;
     	ADDRESSU=CLAMP;
        ADDRESSV=CLAMP;
        ADDRESSW=CLAMP;
      };
   texture GlowVColorTX 
      <
      	string Name = " ";
      >;
   sampler2D GlowVColor=sampler_state 
      {
	Texture=<GlowVColorTX>;
     	ADDRESSU=CLAMP;
        ADDRESSV=CLAMP;
        ADDRESSW=CLAMP;
      };

//--------------
// structs 
//--------------
   struct InPut
     {
 	float4 pos:POSITION; 
 	float2 UV:TEXCOORD; 
     };
   struct OutPut
     {
 	float4 opos:POSITION;  
 	float2 Tex1:TEXCOORD0;  
 	float2 Tex2:TEXCOORD1;  
 	float2 Tex3:TEXCOORD2;  
 	float2 Tex4:TEXCOORD3;  
     };

//--------------
// vertex shader
//--------------
   OutPut VS(InPut IN) 
     {
 	OutPut OUT;
 	OUT.opos=IN.pos;
 	OUT.Tex1=IN.UV;
  	OUT.Tex2=IN.UV+0.5*float2(ViewScaleX,ViewScaleY);
 	OUT.Tex3=0;
 	OUT.Tex4=0;
 	return OUT;
    }
   OutPut VSH1(InPut IN) 
     {
 	OutPut OUT;
 	OUT.opos=IN.pos;
  	OUT.Tex1=(IN.UV+0.5*float2(ViewScaleX,ViewScaleY))+(float2(BlurOffset,0)*0.1f);
  	OUT.Tex2=(IN.UV+0.5*float2(ViewScaleX,ViewScaleY))+(float2(BlurOffset,0)*1.1f);
  	OUT.Tex3=(IN.UV+0.5*float2(ViewScaleX,ViewScaleY))+(float2(BlurOffset,0)*2.1f);
  	OUT.Tex4=(IN.UV+0.5*float2(ViewScaleX,ViewScaleY))+(float2(BlurOffset,0)*3.1f);
 	return OUT;
    }
   OutPut VSH2(InPut IN) 
     {
 	OutPut OUT;
 	OUT.opos=IN.pos;
  	OUT.Tex1=(IN.UV+0.5*float2(ViewScaleX,ViewScaleY))-(float2(BlurOffset,0)*0.1f);
  	OUT.Tex2=(IN.UV+0.5*float2(ViewScaleX,ViewScaleY))-(float2(BlurOffset,0)*1.1f);
  	OUT.Tex3=(IN.UV+0.5*float2(ViewScaleX,ViewScaleY))-(float2(BlurOffset,0)*2.1f);
  	OUT.Tex4=(IN.UV+0.5*float2(ViewScaleX,ViewScaleY))-(float2(BlurOffset,0)*3.1f);
 	return OUT;
    }
   OutPut VSV1(InPut IN) 
     {
 	OutPut OUT;
 	OUT.opos=IN.pos;
  	OUT.Tex1=(IN.UV+0.5*float2(ViewScaleX,ViewScaleY))+(float2(0,BlurOffset)*0.1f);
  	OUT.Tex2=(IN.UV+0.5*float2(ViewScaleX,ViewScaleY))+(float2(0,BlurOffset)*1.1f);
  	OUT.Tex3=(IN.UV+0.5*float2(ViewScaleX,ViewScaleY))+(float2(0,BlurOffset)*2.1f);
  	OUT.Tex4=(IN.UV+0.5*float2(ViewScaleX,ViewScaleY))+(float2(0,BlurOffset)*3.1f);
 	return OUT;
    }
   OutPut VSV2(InPut IN) 
     {
 	OutPut OUT;
 	OUT.opos=IN.pos;
  	OUT.Tex1=(IN.UV+0.5*float2(ViewScaleX,ViewScaleY))-(float2(0,BlurOffset)*0.1f);
  	OUT.Tex2=(IN.UV+0.5*float2(ViewScaleX,ViewScaleY))-(float2(0,BlurOffset)*1.1f);
  	OUT.Tex3=(IN.UV+0.5*float2(ViewScaleX,ViewScaleY))-(float2(0,BlurOffset)*2.1f);
  	OUT.Tex4=(IN.UV+0.5*float2(ViewScaleX,ViewScaleY))-(float2(0,BlurOffset)*3.1f);
 	return OUT;
    }

//--------------
// pixel shader
//--------------
  float4 DownSamplePS(OutPut IN)  : COLOR
     {
	float3 color=tex2D(RenderColor,IN.Tex2);
	return float4(pow(color,10),1);		
     }  
   float4 BlurPS(OutPut IN, uniform sampler2D texmap)  : COLOR
     {
	float3 color=tex2D(texmap,IN.Tex1);
	color +=tex2D(texmap,IN.Tex2);
	color +=tex2D(texmap,IN.Tex3);
	color +=tex2D(texmap,IN.Tex4);
	return float4(color*0.175f,1);	
     } 
   float4 FinalCompPS(OutPut IN)  : COLOR
     {
	float3 Scene = tex2D(RenderColor,IN.Tex1);
	float3 Blur = tex2D(GlowVColor,IN.Tex2);
	return float4(Scene+(Blur*GlowIntensity),MotionBlur);	
     }  

//--------------
// techniques   
//--------------
    technique DownSample
      {
  	pass p1
      {		
  	vertexShader = compile vs_1_1 VS(); 
  	pixelShader  = compile ps_1_4 DownSamplePS(); 	
      }
      }
    technique GlowHPassA
      {
  	pass p1
      {		
  	vertexShader = compile vs_1_1 VSH1(); 
   	pixelShader  = compile ps_1_4 BlurPS(DownColor);	
      }
  	pass p2
      {		
  	vertexShader = compile vs_1_1 VSH2(); 
  	pixelShader  = compile ps_1_4 BlurPS(DownColor);
	AlphaBlendEnable = True;
 	SrcBlend = One;
 	DestBlend = One;	
      }
      }
    technique GlowVPassA
      {
  	pass p1
      {		
  	vertexShader = compile vs_1_1 VSV1(); 
   	pixelShader  = compile ps_1_4 BlurPS(GlowHColor);	
      }
  	pass p2
      {		
  	vertexShader = compile vs_1_1 VSV2(); 
  	pixelShader  = compile ps_1_4 BlurPS(GlowHColor);
	AlphaBlendEnable = True;
 	SrcBlend = One;
 	DestBlend = One;	
      }
      }
    technique GlowHPassB
      {
  	pass p1
      {		
  	vertexShader = compile vs_1_1 VSH1(); 
   	pixelShader  = compile ps_1_4 BlurPS(GlowVColor);	
      }
  	pass p2
      {		
  	vertexShader = compile vs_1_1 VSH2(); 
  	pixelShader  = compile ps_1_4 BlurPS(GlowVColor);
	AlphaBlendEnable = True;
 	SrcBlend = One;
 	DestBlend = One;	
      }
      }
    technique GlowVPassB
      {
  	pass p1
      {		
  	vertexShader = compile vs_1_1 VSV1(); 
   	pixelShader  = compile ps_1_4 BlurPS(GlowHColor);	
      }
  	pass p2
      {		
  	vertexShader = compile vs_1_1 VSV2(); 
  	pixelShader  = compile ps_1_4 BlurPS(GlowHColor);
	AlphaBlendEnable = True;
 	SrcBlend = One;
 	DestBlend = One;	
      }
      }
    technique FinalComp
      {
  	pass p1
      {		
  	vertexShader = compile vs_1_1 VS(); 
  	pixelShader  = compile ps_1_4 FinalCompPS(); 	
      }
      }
