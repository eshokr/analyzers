// Original Author:  Eslam Shokr
//         Created:  sun, 23 Dec 2018 22:36:50 GMT
//
//


// system include files
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

  edm::Service<TFileService> fs;
   histo1 = fs->make<TH1D>("eta(0.1)" , "eta(0.1)" , 100 , 0 , 500 );
   histo2 = fs->make<TH1D>("eta(0.2)" , "eta(0.2)" , 100 , 0 , 700 );
   histo5 = fs->make<TH1D>("eta(0.5)" , "eta(0.5)" , 100 , 0 , 1000 );   

   
   histoNo = fs->make<TH1D>("tracksno." , "tracksno." , 100 , 0 , 3000 );


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
   using namespace edm;
   using namespace std;
   Handle<reco::TrackCollection> tracks;
       iEvent.getByLabel("generalTracks", tracks); 
   Handle<vector<reco::Vertex> > primary_vertices;
       iEvent.getByLabel("offlinePrimaryVertices", primary_vertices);
   // print the number of primary vertex in this event to screen
cout << "the number of primary vertices in this event is = " << primary_vertices - > size () << endl;
   
   // to print the number of tracks in the primary vertices. also print the vertex position in z and rho
   for (vector<reco::Vertex>::const_iterator vertices = primary_vertices->begin() ; vertices != primary_vertices->end(); vertices ++ )
   {
   cout << "   Vertex has nTracks: " << vertices ->nTracks() << " and tracksSize:" << vertices ->tracksSize() << endl;
       cout << "position in z = " << vertices ->position().z() << " position in rho = " << vertices -> position().Rho() << endl;
   }
   
   int k1 =0; int y2 =0; int m5 =0; int l =0; int s =0; int z =0;
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
       
   for (reco::TrackCollection::const_iterator track1 = tracks->begin() ; track1 != tracks->end(); track1 ++ )
   {
      // tracks selection for track1
if (track1 -> quality(reco::Track::qualityByName("highPurity"))                 // 1- high quality
     && abs (track1 -> eta()) < 2.4                                             // 2- |η| < 2.4
     &&track1 ->pt() >0.1 && track1 ->pt() <5.0                                 // 3- pt  0.1 GeV/c < pt <5.0 GeV/c.
     &&track1 ->ptError()/track1 ->pt() < 0.1                                   // 4- σ(pT)/pT < 10 %
     &&abs(track1 ->dz())/ track1 ->dzError() < 3.0                             // 5- dz/ σ(dz) < 3
     &&abs(track1 ->dxy())/ track1 ->dxyError() < 3.0      )                    // 6- dxy/ σ(dxy) <3
                                                                           
       if (abs(track ->eta() - track1 ->eta()) <= 0.1)
     { k1 =k1+1;}
  
       if (abs(track ->eta() - track1 ->eta()) <= 0.2)
     { y2 =y2+1;}   
      
       if (abs(track ->eta() - track1 ->eta()) <= 0.5)
     { m5 =m5+1;}   
   
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
       k1 =0; y2 =0; m5 =0; }
   
   histoNo ->Fill(tracks ->size());
   cout <<"the number of tracks in this event = " << tracks ->size()<<endl;
   
   histo1 ->Fill(l);
   cout <<"the maximum no of tracks with respect to 0.1 window  = "<< l << endl;

   histo2 ->Fill(z);
   cout <<"the maximum no of tracks with respect to 0.2 window  = "<< z << endl;
  
   histo5 ->Fill(s);
   cout <<"the maximum no of tracks with respect to 0.5 window  = "<< s << endl;
  
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
}

// ------------ method called once each job just after ending the event loop  ------------
void 
DemoAnalyzer5::endJob() 
{
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
