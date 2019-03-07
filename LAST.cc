#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Candidate/interface/VertexCompositeCandidate.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "TFile.h"
#include <TGraph.h>
#include "TH1.h"

//
// class declaration
//

class DemoAnalyzer5 : public edm::EDAnalyzer {
   public:
      explicit DemoAnalyzer5(const edm::ParameterSet&);
      ~DemoAnalyzer5();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:

	// configuration parameters

	edm::EDGetTokenT<std::vector<reco::Track>> tracksToken_;
	edm::EDGetTokenT<reco::BeamSpot> beamSpotToken_;
         //edm::EDGetTokenT<edm::View<reco::Vertex>> primary_verticesToken_;  
         edm::EDGetTokenT<std::vector<reco::Vertex> > vertexToken_;


      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
  TH1D* histo1;
  TH1D* histo2;
  TH1D* histo5;
   
  TH1D* histoNo;
    TH1D* histoSl;
  //TGraph* g;
  //TFile* f;

int i =0;
int j =0;
int p=0;

int k1 =0; int y2 =0; int m5 =0; int l =0; int s =0; int z =0; int u=0;
//TGraph* graphno;
double dxxy=0.0; double dzz=0.0;



};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
DemoAnalyzer5::DemoAnalyzer5(const edm::ParameterSet& iConfig)
{
	tracksToken_ = mayConsume<std::vector<reco::Track> >(iConfig.getParameter<edm::InputTag> ("trck"));
	vertexToken_ = mayConsume<std::vector<reco::Vertex>>(iConfig.getParameter<edm::InputTag>("vrtx"));
	beamSpotToken_ = consumes<reco::BeamSpot>(iConfig.getParameter<edm::InputTag>("bmspt"));
}


DemoAnalyzer5::~DemoAnalyzer5()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
DemoAnalyzer5::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
i = i+1;

   using namespace edm;
   using namespace std;
cout <<"************************** begining of the event no( " << i << " )*****************************" << endl;
//cout << "the number of this event is "<<i << endl;

// handles

Handle<vector<reco::Track>> tracks;
Handle<vector<reco::Vertex>> primary_vertices;
Handle<reco::BeamSpot> beamSpot;

vector <const reco::Vertex*> vertexvector;






//double a = vx ->tracksSize();


// read beamspot 
	iEvent.getByToken(beamSpotToken_, beamSpot);
// read tracks
         iEvent.getByToken(tracksToken_, tracks);
// read primary vertices 
        iEvent.getByToken(vertexToken_, primary_vertices);

const reco::Vertex *vx = &(*primary_vertices ->begin());

//for loop to arrange the vertices again
 for (vector<reco::Vertex>::const_iterator vertices1 = primary_vertices->begin() ; vertices1 != primary_vertices->end(); vertices1 ++ )
{
if (vertices1 ->tracksSize()> vx ->tracksSize())
{
vertexvector.push_back(&*vertices1);
}
if (vertices1 ->tracksSize()== vx ->tracksSize())
{
vertexvector.push_back(&*vertices1);
}}

const reco::Vertex *vxx = *vertexvector.begin();

// to print vertexvector component 
cout <<"the number of vertices after selection " << vertexvector.size()<<endl;




 



dxxy = vx->position().Rho();
dzz = vx ->position().Z();
cout <<"***********************************************************************"<<endl;
cout << "the 1st primary vertex has "<<vx ->tracksSize() << " number of tracks" <<endl;
cout <<"position of the 1st primary vertex in z "<<vx ->position().Z()<<" && in rho "<<vx ->position().Rho() <<endl; 
cout <<"***********************************************************************"<<endl;


  // print the number of primary vertex in this event to screen
cout <<"----------------------------------------------------------------------------------" <<endl;
cout << " ^_^ ^_^ the number of primary vertices in this event is = " << primary_vertices -> size () << endl;
   
   // to print the number of tracks in the primary vertices. also print the vertex position in z and rho
   for (vector<reco::Vertex>::const_iterator vertices = primary_vertices->begin() ; vertices != primary_vertices->end(); vertices ++ )
   {
 if(!vertices->isFake()) {
u = u+1;
cout <<"----------------------------------------------------------------------------------" <<endl; 
cout <<"the number of this vertex is "<< u <<endl;
   cout << "  => Vertex has nTracks: " << vertices ->nTracks() << " and tracksSize:" << vertices ->tracksSize() << endl;
   cout << "  => position of vertex in z = " << vertices ->position().z() << " && in rho = " << vertices -> position().Rho() << endl;
cout <<"----------------------------------------------------------------------------------" <<endl; 
//cout << "    ===> position of the vertex with maximum no of tracks in z = " << dzz << " && in rho = " << dxxy << endl;

if (vertices ->tracksSize() >= vx ->tracksSize())
{
dxxy = vertices ->position().Rho();
dzz = vertices ->position().Z();


}
 
//cout <<"-------------------------------------------------------------------" <<endl;  
}

}
cout <<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
 cout << "    ===> position of the vertex with maximum no of tracks in z = " << dzz << " && in rho = " << dxxy << endl;
cout <<"      ===> position of the vertex with maxium no of tracks after selction in Z = " <<vxx->position().Z() <<" && in rho= "<<vxx->position().Rho() <<endl; 
cout <<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;

for (reco::TrackCollection::const_iterator track2 = tracks->begin() ; track2 != tracks->end(); track2 ++ )
   {

if (track2 -> quality(reco::Track::qualityByName("highPurity"))                  // 1- high quality     
&& abs(track2 -> eta()) < 2.4                                              // 2- |η| < 2.4
     && track2 ->pt() >0.1 && track2 ->pt() <5.0                                  // 3- pt  0.1 GeV/c < pt <5.0 GeV/c.
     && track2 ->ptError()/track2 ->pt() < 0.1                                    // 4- σ(pT)/pT < 10 %
     && abs(track2 ->dz()/ abs(track2 ->dzError()) < 3.0                              // 5- dz/ σ(dz) < 3
     && abs(track2 ->dxy())/abs(track2 ->dxyError()) < 3.0    )) 
j = j+1;

}

for (reco::TrackCollection::const_iterator track3 = tracks->begin() ; track3 != tracks->end(); track3 ++ )
   {

if (track3 -> quality(reco::Track::qualityByName("highPurity"))                  // 1- high quality     
&& abs(track3 -> eta()) < 2.4                                              // 2- |η| < 2.4
     && track3 ->pt() >0.1 && track3 ->pt() <5.0                                  // 3- pt  0.1 GeV/c < pt <5.0 GeV/c.
     && track3 ->ptError()/track3 ->pt() < 0.1                                    // 4- σ(pT)/pT < 10 %
     && abs(track3 ->dz(vxx ->position()))/ abs(track3 ->dzError()) < 3.0                              // 5- dz/ σ(dz) < 3
     && abs(track3 ->dxy(vxx ->position()))/abs(track3 ->dxyError()) < 3.0    ) 
p = p+1;

}



   
   for (reco::TrackCollection::const_iterator track = tracks->begin() ; track != tracks->end(); track ++ )
   {
       // tracks selection for track
         // 1- high quality
if (track -> quality(reco::Track::qualityByName("highPurity"))                  // 1- high quality
     && abs (track -> eta()) < 2.4                                              // 2- |η| < 2.4
     && track ->pt() >0.1 && track ->pt() <5.0                                  // 3- pt  0.1 GeV/c < pt <5.0 GeV/c.
     && track ->ptError()/track ->pt() < 0.1                                    // 4- σ(pT)/pT < 10 %
     && abs(track ->dz())/ track ->dzError() < 3.0                              // 5- dz/ σ(dz) < 3
     && abs(track ->dxy())/ track ->dxyError() < 3.0    )                       // 6- dxy/ σ(dxy) <3
       // numer of tracks after selections
//{j = j+1;
{
   for (reco::TrackCollection::const_iterator track1 = tracks->begin() ; track1 != tracks->end(); track1 ++ )
   {
      // tracks selection for track1
if (track1 -> quality(reco::Track::qualityByName("highPurity"))                 // 1- high quality
     && abs (track1 -> eta()) < 2.4                                             // 2- |η| < 2.4
     &&track1 ->pt() >0.1 && track1 ->pt() <5.0                                 // 3- pt  0.1 GeV/c < pt <5.0 GeV/c.
     &&track1 ->ptError()/track1 ->pt() < 0.1                                   // 4- σ(pT)/pT < 10 %
     &&abs(track1 ->dz())/ track1 ->dzError() < 3.0                             // 5- dz/ σ(dz) < 3
     &&abs(track1 ->dxy())/ track1 ->dxyError() < 3.0      )                    // 6- dxy/ σ(dxy) <3
{                                                                           
       if (abs(track ->eta() - track1 ->eta()) <= 0.1)
     { k1 =k1+1;}
  
       if (abs(track ->eta() - track1 ->eta()) <= 0.2)
     { y2 =y2+1;}   
      
       if (abs(track ->eta() - track1 ->eta()) <= 0.5)
     { m5 =m5+1;}   
 }}  
   }
   // k is for 0.1 for loop and l is the maxmium for 0.1
      if(k1 > l)
               { l =k1;}
   // z is for 0.2 for loop and z is the maxmium for 0.2
       if(y2 > z)
               { z =y2;} 
   // m is for 0.1 for loop and s is the maxmium for 0.5
       if(m5 > s)
               { s =m5;}
   // after fishing for loop and give numbers for l, z and s make k, m and y zero again for the second loop;
       k1 =0; y2 =0; m5 =0; }//}
   
   histoNo ->Fill(tracks ->size());
//cout <<"-----------------------------------------------------------------"<<endl;   
cout <<"----------------------------------------------------------------------------------" <<endl;
cout <<"*** the number of tracks in this event = " << tracks ->size()<<endl;
 //  g ->SetPoint(1,i,tracks ->size());
histoSl ->Fill(j);
cout <<"*** the numer of tracks 1st after selection in this event = " <<j <<endl;
j=0;

cout <<"*** the numer of tracks  2nd after selection in this event = " <<p <<endl;
p=0;

   histo1 ->Fill(l);
cout <<"======================================================================================"<<endl;
   cout <<"         the maximum no of tracks with respect to 0.1 window  = "<< l << endl;
l =0;
   histo2 ->Fill(z);
   cout <<"         the maximum no of tracks with respect to 0.2 window  = "<< z << endl;
z=0;
   histo5 ->Fill(s);
   cout <<"         the maximum no of tracks with respect to 0.5 window  = "<< s << endl;
s=0;  u =0;dxxy =0.0 ; dzz =0.0;
//cout <<"======================================================================================="<<endl;
cout <<"======================================================================================"<<endl;
cout <<"********************************** ending of the event *******************************" <<endl;
//}
#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif

}

// ------------ method called once each job just before starting event loop  ------------
void 
DemoAnalyzer5::beginJob()
{



  edm::Service<TFileService> fs;

//histograms
   histo1 = fs->make<TH1D>("eta(0.1)" , "eta(0.1)" , 100 , 0 , 80 );
   histo2 = fs->make<TH1D>("eta(0.2)" , "eta(0.2)" , 100 , 0 , 200 );
   histo5 = fs->make<TH1D>("eta(0.5)" , "eta(0.5)" , 100 , 0 , 300 );   
   histoNo = fs->make<TH1D>("tracksno." , "tracksno." , 600 , 0 , 15000 );
   histoSl = fs->make<TH1D>("trackssl." , "tracksSl." , 100 , 0 , 500 );
  //graphno = fs->make<TH1D>("gtracksno." , "gtracksno." , 1000 , 0 , 15000 );
//f= new TFile ("test.root","RECREATE");
//g = new TGraph();
//int i =0;

}

// ------------ method called once each job just after ending the event loop  ------------
void 
DemoAnalyzer5::endJob() 
{
//g->Write();
//f->Close();

}

// ------------ method called when starting to processes a run  ------------
/*
void 
DemoAnalyzer5::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
DemoAnalyzer5::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
DemoAnalyzer5::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
DemoAnalyzer5::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
DemoAnalyzer5::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(DemoAnalyzer5);
