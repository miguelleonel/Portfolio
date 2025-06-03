Project sample of my Independent Study/Graduate Project at UTSA. 

This directory is just the code subset of the greater goal. 

The end goal was to simulate an airport customs checkpoint conversation, in Spanish, where the agent response is simulated and the user interacts with it.
Agent response is a Llama LLM and the user's voice is interpretted by the local system, all aided with a VR simulation. 

The overall data flow will be summarized as follows.
The project required the use of a local offline model, which was the main constraint as this required the model to be pretrained, local, and able to run on consumer level hardware.

The open-source LLM by Meta was tested for functionality. The Llama 2 chat model, specifically the one found on HuggingFace at "meta-llama/Llama-2-7b-chat-hf" was tested for Spanish conversation with a basic prompt explaining it's purpose. 

After some testing, it was found to quickly revert to English responses after a response or two in Spanish. This set the baseline and necesitated the use of fine-tuning this model. 
Data from OpenAI's model, specifically "gpt-3.5-turbo-0125", was found to be fairly accurate in conversational Spanish responses, with only variance in responses quickly found to be the first issue. This was sufficient for generating the fine-tuning dataset. 

The OpenAI API was used for generating 10,000 conversations, with some complicated circumstances that need explaining to help understand how this was done. 
The TLDR is that we have to simulate both sides of the conversation and also have a hard-coded number of turns in the conversation if the goal is plentiful unique conversations. 

The OpenAI API code to generate the initial data had to be uploaded with the Agent prompt, and download a ".jsonl" output file after the request was processed. 
The other side of the conversation was similary setup, but with the User prompt instead. The initial Agent response was relayed along with this API request, and the chain of conversation history begins here. 
Variability in the conversations was aided with a mix of hyperparameter values and user/agent attributes all randomly chosen during prompt generation. 

This data generation script continues to go back and forth, making use of batch processing to aid in both generating expansive data and cutting costs 50%, as OpenAI discounts batch-processed data 50%. 
A hard-coded number of turns was chosen at 10 turns as this was enough turns for some conversations to finish, but others were still cut-off. This was a known issue that was easier to work with rather than to fix accurately, as useable data was the goal. 

After that process, a pair of 10,000 conversation .jsonl files were generated, with the User response the last turn of the conversation, and the unique prompts of both Agent and User were kept within their files.

This data was compiled together and 'pickled' to be processed during the fine-tuning process. 
The default Llama 2 7B Chat model was fine-tuned on this data from OpenAI on a remote server supplied by UTSA. More info on ARC can be found here:  https://www.utsa.edu/techsolutions/ResearchSupport/hpc.html

This new fine-tuned model was then tested and this specific model can be found on my HuggingFace account: https://huggingface.co/migleolop/Sep1FineTune

The model was then compared against the base model in a 1 to 1 comparison, in both automatic metrics and conversation output. 

Overall, the model showed improvement to stay in character, respond only in Spanish, and metrics favored the fine-tuned model, albeit some neglibile improvement but improvement overall nonetheless.

Demo to customer was received favorably and future work would involve upgrading to Llama 3. 
VR unity server lost documentation and lacked personnel resources, ie. VR setting was being worked on but the python script hosting the server was not launching the local LLM correctly. 
Presentation showcased both attributes separately. 
